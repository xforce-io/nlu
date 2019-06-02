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

void Matcher::Match(basic::NluContext &nluContext) {
  ParseCommon_(nluContext);
  ParseAccordingToRule_(nluContext);
}

void Matcher::ParseCommon_(basic::NluContext &nluContext) {
  auto &segments = nluContext.GetSegments();
  auto &chunkSeps = nluContext.GetChunkSeps();
  for (size_t i=0; i < segments.Size(); ++i) {
    auto curClassOfPosTags = segments[i]->GetClassOfPosTags();
    if (basic::PosTag::Class::kUndef == curClassOfPosTags) {
      continue;
    }

    if (basic::PosTag::Class::kFuncWord == curClassOfPosTags ||
        basic::PosTag::Class::kMood == curClassOfPosTags ||
        basic::PosTag::Class::kPunctuation == curClassOfPosTags) {
      chunkSeps.Add(std::make_shared<basic::ChunkSep>(i));
      if (i != segments.Size() - 1) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>(i+1));
      }
    }

    if (i != segments.Size() - 1) {
      auto nextClassOfPosTags = segments[i+1]->GetClassOfPosTags();
      if (basic::PosTag::Class::kUndef == nextClassOfPosTags) {
        continue;
      }

      if (basic::PosTag::Class::kNominal == curClassOfPosTags &&
          (basic::PosTag::Class::kPredicate == nextClassOfPosTags||
           basic::PosTag::Class::kAdvOrDis == nextClassOfPosTags)) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>(i+1));
      } else if ((basic::PosTag::Class::kPredicate == curClassOfPosTags ||
                  basic::PosTag::Class::kAdvOrDis == curClassOfPosTags) &&
                 basic::PosTag::Class::kNominal == nextClassOfPosTags) {
        chunkSeps.Add(std::make_shared<basic::ChunkSep>(i+1));
      }
    }
  }
}

void Matcher::ParseAccordingToRule_(basic::NluContext &nluContext) {
  auto context = std::make_shared<milkie::Context>(nluContext.GetQuery());
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
      for (auto &segment : nluContext.GetSegments().GetAll()) {
        for (auto &storageItem : storageItems) {
          if (segment->GetOffset() == storageItem.GetOffset() ||
              segment->GetOffset() == storageItem.GetOffset() + storageItem.GetLen()) {
            nluContext.GetChunkSeps().Add(basic::ChunkSep(segment->GetOffset()));
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
        nluContext.GetChunks().Add(chunk);
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
