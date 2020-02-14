#include "../matcher.h"
#include "../../conf/conf.h"
#include "../parser/filter_parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

const std::wstring Matcher::kChunkStoragePrefix = L"/chunkSep";
const std::wstring Matcher::kSyntacticStoragePrefix = L"/syntactic";

Matcher::Matcher() :
    parser_(new milkie::Milkie()) {
  filterParserCommons_.push_back(new FPCDongjieAndDongqu());
  filterParserCommons_.push_back(new FPCMid());
  filterParserCommons_.push_back(new FPCSurround());
}

Matcher::~Matcher() {
  for (auto *filterParserCommon : filterParserCommons_) {
    delete filterParserCommon;
  }
  XFC_DELETE(parser_)
}

bool Matcher::Init() {
  bool ret = parser_->Init(Conf::Get().GetParserConfpath());
  if (!ret) {
    FATAL("fail_init[parser]");
    return false;
  }

  featureExtractor_ = parser_->GetManager().GetFeatureExtractor(L"chunker");
  if (nullptr == featureExtractor_) {
    FATAL("fail_get_feature_extractor_named_chunker");
    return false;
  }
  return true;
}

void Matcher::Match(std::shared_ptr<basic::NluContext> nluContext) {
  nluContext->Add(basic::ChunkSep(0));

  ParseAccordingToRule_(nluContext);
  ParseCommon_(*nluContext);
}

void Matcher::ParseAccordingToRule_(std::shared_ptr<basic::NluContext> nluContext) {
  auto context = std::make_shared<milkie::Context>(nluContext);
  auto errCode = featureExtractor_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return;
  }

  const milkie::Storage &storage = context->GetStorage();
  for (auto &storageKv : storage.Get()) {
    const milkie::StorageKey &key = storageKv.first;
    std::wstring repr;
    key.GetRepr(repr);

    std::vector<std::wstring> vals;
    StrHelper::SplitStr(repr, L'.', vals);
    if (vals.size() != 2) {
      continue;
    }

    auto storageItems = storageKv.second->Get();
    if (vals[0] == kChunkStoragePrefix) {
      for (auto &segment : nluContext->GetSegments().GetAll()) {
        for (auto &storageItem : storageItems) {
          if (segment->GetOffset() == storageItem.GetOffset() ||
              segment->GetOffset() == storageItem.GetOffset() + storageItem.GetLen()) {
            nluContext->Add(basic::ChunkSep(segment->GetOffset()));
          }
        }
      }
    } else if (vals[0] == kSyntacticStoragePrefix) {
      if (vals.size() != 2) {
        ERROR("invalid_storage_key[" << repr << "]");
        continue;
      }

      auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
      if (basic::SyntaxTag::Type::kUndef == syntaxTag) {
        ERROR("unknown_syntax_tag[" << syntaxTag << "]");
        continue;
      }

      auto storageItems = storageKv.second->Get();
      for (auto &storageItem : storageItems) {
        basic::Chunk chunk(
                *nluContext,
                syntaxTag,
                storageItem.GetOffset(),
                storageItem.GetContent().length(),
                310);
        nluContext->Add(chunk);
        nluContext->Add(basic::ChunkSep(storageItem.GetOffset()));
        nluContext->Add(basic::ChunkSep(
                storageItem.GetOffset() + storageItem.GetContent().length()));
      }
    } else {
      FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
    }
  }
}

void Matcher::ParseCommon_(basic::NluContext &nluContext) {
  auto &segments = nluContext.GetSegments().GetAll();
  auto cur = segments.begin();
  while (cur != segments.end()) {
    auto next = cur;
    ++next;

    if (segments.end() != next) {
      for (auto *fpc : filterParserCommons_) {
        int chunkPos = 0;
        auto syntaxTag = basic::SyntaxTag::Type::kUndef;
        fpc->Filter(
                nluContext,
                *cur,
                *next,
                chunkPos,
                syntaxTag);

        ParserCommon::Process(
                nluContext,
                *cur,
                *next,
                chunkPos,
                syntaxTag);
        if (0!=chunkPos) {
          break;
        }
      }
    } else {
      for (auto *fpc : filterParserCommons_) {
        int chunkPos = 0;
        auto syntaxTag = basic::SyntaxTag::Type::kUndef;
        fpc->Filter(
                nluContext,
                *cur,
                nullptr,
                chunkPos,
                syntaxTag);

        ParserCommon::Process(
                nluContext,
                *cur,
                nullptr,
                chunkPos,
                syntaxTag);
        if (0!=chunkPos) {
          break;
        }
      }
    }
    cur = next;
  }
}

}}}
