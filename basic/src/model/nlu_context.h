#pragma once

#include "../public.h"
#include "fragment/manager_fragment_set.h"
#include "semantic_unit/semantic_unit_entity.h"

namespace xforce { namespace nlu { namespace basic {

class Phrase;
class CollectionSyntaxTag;

class NluContext {
 public:
  explicit NluContext(const std::wstring &query);
  virtual ~NluContext();

  const std::wstring& GetQuery() const { return query_; }

  inline void SetIsValid(bool isValid);

  template <typename FragmentType>
  void Set(const typename FragmentType::Set &set) const;

  void AddPhrase(
          size_t from,
          size_t len,
          std::shared_ptr<CollectionSyntaxTag> collectionSyntaxTag,
          uint32_t strategy);

  template <typename FragmentType>
  bool Add(const FragmentType &fragment);

  template <typename FragmentType>
  bool Add(const std::shared_ptr<FragmentType> &fragment);

  inline void Clear();

  std::shared_ptr<NluContext> Build(size_t from, size_t to);
  std::shared_ptr<NluContext> Clone() const;
  void Reset(basic::Stage::Val stage);

  inline bool GetIsValid(bool check = false);
  const std::vector<Phrase>& GetPhrases() const { return phrases_; }

  template <typename FragmentType>
  const typename FragmentType::Set& Get() const;

  template <typename FragmentType>
  typename FragmentType::Set& Get();

  template <typename FragmentType>
  void GetFragmentBefore(
          size_t offset,
          std::vector<std::shared_ptr<FragmentType>> &result) const;

  template <typename FragmentType>
  void GetFragmentAfter(
          size_t offset,
          std::vector<std::shared_ptr<FragmentType>> &result) const;

  inline bool HasPredPosBefore(size_t offset) const;

  void Dump(JsonType &jsonType, const NluContext *diff= nullptr) const;
  void Dump(std::string &json) const;

 private:
  std::wstring query_;
  bool isValid_;
  ManagerFragmentSet *managerFragmentSet_;

  std::vector<Phrase> phrases_;
};

void NluContext::SetIsValid(bool isValid) {
  isValid_ = isValid;
}

template <typename FragmentType>
void NluContext::Set(const typename FragmentType::Set &set) const {
  managerFragmentSet_->Set(set);
}

template <typename FragmentType>
bool NluContext::Add(const FragmentType &fragment) {
  return managerFragmentSet_->Get<FragmentType>().Add(fragment);
}

template <>
inline bool NluContext::Add(const ChunkSep &chunkSep) {
  auto iter = managerFragmentSet_->Get<Chunk>().Begin();
  while (iter != managerFragmentSet_->Get<Chunk>().End()) {
    auto next = iter;
    ++next;
    if ((*iter)->GetTag() == SyntaxTag::Type::kContNp &&
        (*iter)->GetOffset() < chunkSep.GetOffset() &&
        chunkSep.GetOffset() < (*iter)->GetEnd()) {
      managerFragmentSet_->Get<Chunk>().Add(
              Chunk(
                      *this,
                      SyntaxTag::Type::kContNp,
                      (*iter)->GetOffset(),
                      chunkSep.GetOffset() - (*iter)->GetOffset()));
      managerFragmentSet_->Get<Chunk>().Add(
              Chunk(
                      *this,
                      SyntaxTag::Type::kContNp,
                      chunkSep.GetOffset(),
                      (*iter)->GetEnd() - chunkSep.GetOffset()));
      managerFragmentSet_->Get<Chunk>().Erase(iter);
    }
    iter = next;
  }
  return managerFragmentSet_->Get<ChunkSep>().Add(chunkSep);
}

template <>
inline bool NluContext::Add(const Chunk &chunk) {
  if (chunk.GetClassOfSyntaxTags() == SyntaxTag::Class::kNp) {
    auto &chunkSet = managerFragmentSet_->Get<Chunk>();

    bool touched = true;
    while (touched) {
      touched = false;
      auto iter = chunkSet.GetAll().begin();
      while (iter != chunkSet.GetAll().end()) {
        auto &contChunk = *iter;
        if (contChunk->GetTag() == SyntaxTag::Type::kContNp) {
          if (contChunk->GetOffset() < chunk.GetOffset() &&
              contChunk->GetEnd() > chunk.GetOffset() &&
              contChunk->GetEnd() <= chunk.GetEnd()) {
            chunkSet.Add(std::make_shared<basic::Chunk>(
                    *this,
                    SyntaxTag::Type::kContNp,
                    contChunk->GetOffset(),
                    chunk.GetOffset() - contChunk->GetOffset(),
                    contChunk->GetStrategy()));
            chunkSet.Erase(iter);
            touched = true;
          } else if (contChunk->GetEnd() > chunk.GetEnd() &&
                     contChunk->GetOffset() >= chunk.GetOffset() &&
                     contChunk->GetOffset() < chunk.GetEnd()) {
            size_t offset = chunk.GetEnd();
            size_t len = contChunk->GetEnd() - chunk.GetEnd();
            chunkSet.Add(std::make_shared<basic::Chunk>(
                    *this,
                    SyntaxTag::Type::kContNp,
                    offset,
                    len,
                    contChunk->GetStrategy()));
            chunkSet.Erase(iter);
            touched = true;
          }
        }
        ++iter;
      }
    }
  }
  return managerFragmentSet_->Get<Chunk>().Add(chunk);
}

template <typename FragmentType>
bool NluContext::Add(const std::shared_ptr<FragmentType> &fragment) {
  return Add(*fragment);
}

bool NluContext::GetIsValid(bool check) {
  if (check) {
    for (auto &chunk : managerFragmentSet_->Get<Chunk>().GetAll()) {
      if (chunk->ContainTag(SyntaxTag::Type::kNp) &&
          chunk->ContainTag(SyntaxTag::Type::kVp)) {
        isValid_ = false;
        break;
      }
    }
  }
  return isValid_;
}

template <typename FragmentType>
const typename FragmentType::Set& NluContext::Get() const {
  return managerFragmentSet_->Get<FragmentType>();
}

template <typename FragmentType>
typename FragmentType::Set& NluContext::Get() {
  return managerFragmentSet_->Get<FragmentType>();
}

template <typename FragmentType>
void NluContext::GetFragmentBefore(
        size_t offset,
        std::vector<std::shared_ptr<FragmentType>> &result) const {
  Get<FragmentType>().GetFragmentBefore(offset, result);
}

template <>
inline void NluContext::GetFragmentBefore<SemanticUnit>(
        size_t offset,
        std::vector<std::shared_ptr<SemanticUnit>> &result) const {
  std::vector<std::shared_ptr<Chunk>> chunks;
  GetFragmentBefore(offset, chunks);
  for (auto &chunk : chunks) {
    if (chunk->GetSemanticUnit() != nullptr) {
      result.push_back(chunk->GetSemanticUnit());
    }
  }
}

template <>
inline void NluContext::GetFragmentBefore<SemanticUnitEntity>(
        size_t offset,
        std::vector<std::shared_ptr<SemanticUnitEntity>> &result) const {
  std::vector<std::shared_ptr<Chunk>> chunks;
  GetFragmentBefore(offset, chunks);
  for (auto &chunk : chunks) {
    if (chunk->GetSemanticUnit() != nullptr &&
        chunk->GetSemanticUnit()->GetType() == SemanticUnit::Type::kSemanticUnitEntity) {
      result.push_back((std::dynamic_pointer_cast<SemanticUnitEntity>)(chunk->GetSemanticUnit()));
    }
  }
}

template <typename FragmentType>
void NluContext::GetFragmentAfter(
        size_t offset,
        std::vector<std::shared_ptr<FragmentType>> &result) const {
  Get<FragmentType>().GetFragmentAfter(offset, result);
}

template <>
inline void NluContext::GetFragmentAfter<SemanticUnit>(
        size_t offset,
        std::vector<std::shared_ptr<SemanticUnit>> &result) const {
  std::vector<std::shared_ptr<Chunk>> chunks;
  GetFragmentAfter(offset, chunks);
  for (auto &chunk : chunks) {
    if (chunk->GetSemanticUnit() != nullptr) {
      result.push_back(chunk->GetSemanticUnit());
    }
  }
}

template <>
inline void NluContext::GetFragmentAfter<SemanticUnitEntity>(
        size_t offset,
        std::vector<std::shared_ptr<SemanticUnitEntity>> &result) const {
  std::vector<std::shared_ptr<Chunk>> chunks;
  GetFragmentAfter(offset, chunks);
  for (auto &chunk : chunks) {
    if (chunk->GetSemanticUnit() != nullptr &&
        chunk->GetSemanticUnit()->GetType() == SemanticUnit::Type::kSemanticUnitEntity) {
      result.push_back((std::dynamic_pointer_cast<SemanticUnitEntity>)(chunk->GetSemanticUnit()));
    }
  }
}

bool NluContext::HasPredPosBefore(size_t offset) const {
  for (auto &segment : managerFragmentSet_->Get<Segment>().GetAll()) {
    if (segment->GetOffset() < offset &&
        PosTag::IsPredicate(segment->GetTag())) {
      return true;
    }
  }
  return false;
}

}}}
