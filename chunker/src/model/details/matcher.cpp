#include "../matcher.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace chunker {

const std::wstring Matcher::kChunkStoragePrefix = L"chunkSep";
const std::wstring Matcher::kSyntacticStoragePrefix = L"syntactic";

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
          (basic::PosTag::Class::kPredicate == nextClassOfPosTags||
           basic::PosTag::Class::kAdvOrDis == nextClassOfPosTags)) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>((*next)->GetOffset()));
      } else if ((basic::PosTag::Class::kPredicate == curClassOfPosTags ||
                  basic::PosTag::Class::kAdvOrDis == curClassOfPosTags) &&
                 basic::PosTag::Class::kNominal == nextClassOfPosTags) {
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

  std::unordered_map<std::wstring, std::shared_ptr<milkie::StorageVal>> storages;
  context->GetStorages(storages);
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
                storageItem.GetContent().length() + storageItem.GetOffset());
        nluContext->GetChunks().Add(chunk);
      }
    } else {
      FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
    }
  }
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

}}}
