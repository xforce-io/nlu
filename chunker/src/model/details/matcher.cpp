#include "../matcher.h"
#include "../../conf/conf.h"
#include "basic/data/manager.h"
#include "basic/data/gkb/gkb.h"

namespace xforce { namespace nlu { namespace chunker {

const std::wstring Matcher::kChunkStoragePrefix = L"/chunkSep";
const std::wstring Matcher::kSyntacticStoragePrefix = L"/syntactic";

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init(Conf::Get().GetMilkieConfpath());
  if (!ret) {
    FATAL("fail_init[milkie]");
    return false;
  }

  featureExtractor_ = milkie_->GetManager().GetFeatureExtractor(L"chunker");
  if (featureExtractor_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_chunker");
    return false;
  }
  return true;
}

void Matcher::Match(std::shared_ptr<basic::NluContext> nluContext) {
  nluContext->GetChunkSeps().Add(std::make_shared<basic::ChunkSep>(0));

  ParseCommon_(*nluContext);
  ParseAccordingToRule_(nluContext);
  MergeFromDict_(nluContext);
}

void Matcher::ParseCommon_(basic::NluContext &nluContext) {
  auto &segments = nluContext.GetSegments().GetAll();
  auto &chunkSeps = nluContext.GetChunkSeps();
  auto cur = segments.begin();
  while (cur != segments.end()) {
    auto next = cur;
    ++next;

    auto &segment = *cur;
    auto curClassOfPosTags = segment->GetClassOfPosTags();
    if (basic::PosTag::Class::kUndef == curClassOfPosTags) {
      cur = next;
      continue;
    }

    if (basic::PosTag::Class::kFuncWord == curClassOfPosTags ||
        basic::PosTag::Class::kMood == curClassOfPosTags ||
        basic::PosTag::Class::kPunctuation == curClassOfPosTags) {
      chunkSeps.Add(std::make_shared<basic::ChunkSep>(segment->GetOffset()));
      if (next != segments.end()) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>((*next)->GetOffset()));
      }
    }

    if (next != segments.end()) {
      auto nextClassOfPosTags = (*next)->GetClassOfPosTags();
      if (basic::PosTag::Class::kUndef == nextClassOfPosTags) {
        cur = next;
        continue;
      }

      if (basic::PosTag::Class::kNominal == curClassOfPosTags &&
          (basic::PosTag::Class::kPredicate == nextClassOfPosTags ||
              basic::PosTag::Class::kAdv == nextClassOfPosTags)) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>((*next)->GetOffset()));
      } else if ((basic::PosTag::Class::kPredicate == curClassOfPosTags ||
              basic::PosTag::Class::kAdv == curClassOfPosTags) &&
          basic::PosTag::Class::kNominal == nextClassOfPosTags) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>((*next)->GetOffset()));
      } else if (basic::PosTag::Class::kPredicate == curClassOfPosTags &&
          basic::PosTag::Class::kAdv == nextClassOfPosTags) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>((*next)->GetOffset()));
      }
    }
    cur = next;
  }
}

void Matcher::ParseAccordingToRule_(std::shared_ptr<basic::NluContext> nluContext) {
  auto context = std::make_shared<milkie::Context>(nluContext);
  auto errCode = featureExtractor_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return;
  }

  const milkie::Context::Storages &storages = context->GetStorages();
  for (auto &storage : storages) {
    const std::wstring &key = storage.first;
    std::vector<std::wstring> vals;
    StrHelper::SplitStr(key, L'.', vals);
    if (vals.size() != 2) {
      continue;
    }

    auto storageItems = storage.second->Get();
    if (vals[0] == kChunkStoragePrefix) {
      for (auto &segment : nluContext->GetSegments().GetAll()) {
        for (auto &storageItem : storageItems) {
          if (segment->GetOffset() == storageItem.GetOffset() ||
              segment->GetOffset() == storageItem.GetOffset() + storageItem.GetLen()) {
            nluContext->GetChunkSeps().Add(basic::ChunkSep(segment->GetOffset()));
          }
        }
      }
    } else if (vals[0] == kSyntacticStoragePrefix) {
      if (vals.size() != 2) {
        ERROR("invalid_storage_key[" << key << "]");
        continue;
      }

      auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
      if (basic::SyntaxTag::kUndef == syntaxTag) {
        ERROR("unknown_syntax_tag[" << syntaxTag << "]");
        continue;
      }

      auto storageItems = storage.second->Get();
      for (auto &storageItem : storageItems) {
        basic::Chunk chunk(
                syntaxTag,
                storageItem.GetOffset(),
                storageItem.GetContent().length());
        nluContext->GetChunkSeps().Add(basic::ChunkSep(storageItem.GetOffset()));
        nluContext->GetChunkSeps().Add(basic::ChunkSep(
                storageItem.GetOffset() + storageItem.GetContent().length()));
        nluContext->GetChunks().Add(chunk);
      }
    } else {
      FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
    }
  }
}

void Matcher::MergeFromDict_(std::shared_ptr<basic::NluContext> nluContext) {
  auto &segments = nluContext->GetSegments().GetAll();
  auto cur = segments.begin();
  if (cur == segments.end()) {
    return;
  }

  while (true) {
    auto next = cur;
    ++next;
    if (next == segments.end()) {
      return;
    }

    if ((*cur)->GetPosTag() == basic::PosTag::Type::kV &&
        (*next)->GetPosTag() == basic::PosTag::Type::kV) {
      bool ret = basic::Manager::Get().GetGkb().IsPhrase(
              (*cur)->GetStrFromSentence(nluContext->GetQuery()),
              (*next)->GetStrFromSentence(nluContext->GetQuery()));
      if (ret) {
        basic::Chunk chunk(
                basic::SyntaxTag::kVp,
                (*cur)->GetOffset(),
                (*cur)->GetLen() + (*next)->GetLen());
        nluContext->GetChunkSeps().Add(basic::ChunkSep((*cur)->GetOffset()));
        nluContext->GetChunkSeps().Add(basic::ChunkSep((*next)->GetOffset() + (*next)->GetLen()));
      }
    }
    cur = next;
  }
}


Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

}}}
