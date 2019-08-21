#include "../matcher.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace syntax {

const std::wstring Matcher::kSyntacticStoragePrefix = L"/syntactic";

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init(Conf::Get().GetParserConfpath());
  if (!ret) {
    FATAL("fail_init[parser]");
    return false;
  }

  feChunkSep_ = milkie_->GetManager().GetFeatureExtractor(L"syntaxFromChunk");
  if (feChunkSep_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_syntax_from_chunk");
    return false;
  }

  feChunk_ = milkie_->GetManager().GetFeatureExtractor(L"syntax");
  if (feChunk_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_syntax");
    return false;
  }
  return true;
}

void Matcher::Match(std::shared_ptr<basic::NluContext> nluContext) {
  while (Process_(nluContext)) {
  }
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

bool Matcher::Process_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  if (SyntaxProcessForChunkSep_(nluContext)) {
    touched = true;
  }

  if (SyntaxProcessForChunk_(nluContext)) {
    touched = true;
  }

  if (PostProcess_(nluContext)) {
    touched = true;
  }

  AppendixProcess_(nluContext);
  return touched;
}

bool Matcher::SyntaxProcessForChunkSep_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  auto cur = nluContext->GetChunkSeps().Begin();
  while (cur != nluContext->GetChunkSeps().End()) {
    auto next = cur;
    ++next;

    std::shared_ptr<basic::NluContext> fragment;
    if (next != nluContext->GetChunkSeps().End()) {
      fragment = nluContext->Build(
              (*cur)->GetOffset(),
              (*next)->GetOffset());
    } else {
      fragment = nluContext->Build(
              (*cur)->GetOffset(),
              nluContext->GetQuery().length());
    }

    if (fragment == nullptr) {
      cur = next;
      continue;
    }

    auto context = std::make_shared<milkie::Context>(fragment);
    auto errCode = feChunkSep_->MatchPattern(*context);
    if (milkie::Errno::kOk != errCode) {
      cur = next;
      continue;
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
      if (vals[0] == kSyntacticStoragePrefix) {
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
                  syntaxTag,
                  storageItem.GetOffset() + (*cur)->GetOffset(),
                  storageItem.GetContent().length(),
                  410);
          if (nluContext->GetChunks().Add(chunk)) {
            touched = true;
          }
        }
      } else {
        FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
      }
    }
    cur = next;
  }
  return touched;
}

bool Matcher::SyntaxProcessForChunk_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  auto context = std::make_shared<milkie::Context>(nluContext);
  auto errCode = feChunk_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return false;
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
    if (vals[0] == kSyntacticStoragePrefix) {
      auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(vals[1]);
      if (basic::SyntaxTag::Type::kUndef == syntaxTag) {
        ERROR("unknown_syntax_tag[" << syntaxTag << "]");
        return false;
      }

      auto storageItems = storageKv.second->Get();
      for (auto &storageItem : storageItems) {
        basic::Chunk chunk(
                syntaxTag,
                storageItem.GetOffset(),
                storageItem.GetContent().length(),
                420);
        if (nluContext->GetChunks().Add(chunk)) {
          if (basic::SyntaxTag::Type::kStc == syntaxTag) {
            return true;
          }
          touched = true;
        }
      }
    } else {
      FATAL("invalid_chunk_parse_prefix[" << vals[0] << "]");
    }
  }
  return touched;
}

bool Matcher::PostProcess_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (RuleContNp_(nluContext, chunk)) {
      touched = true;
    }

    if (RuleIntransitiveVerb_(nluContext, chunk)) {
      touched = true;
    }
  }
  return touched;
}

void Matcher::AppendixProcess_(std::shared_ptr<basic::NluContext> nluContext) {
  AddAdvpDescDir_(nluContext);
}

bool Matcher::RuleContNp_(
        std::shared_ptr<basic::NluContext> nluContext,
        const std::shared_ptr<basic::Chunk> &chunk) {
  if (chunk->GetTag() != basic::SyntaxTag::Type::kContNp) {
    return false;
  }

  auto segBefore = nluContext->GetSegments().GetFragmentBefore(chunk->GetOffset());
  auto segAfter = nluContext->GetSegments().GetFragmentAfter(chunk->GetOffset() + chunk->GetLen());
  bool beforeCond = (nullptr == segBefore ||
      (basic::PosTag::Type::kV != segBefore->GetTag() &&
          basic::PosTag::Type::kP != segBefore->GetTag()));

  bool afterCond = (nullptr == segAfter ||
      (!basic::PosTag::IsPredicate(segAfter->GetTag()) &&
      basic::PosTag::Type::kP != segBefore->GetTag()));

  if (beforeCond || afterCond) {
    basic::Chunk newChunk(
            basic::SyntaxTag::Type::kNp,
            chunk->GetOffset(),
            chunk->GetLen(),
            430);
    if (nluContext->GetChunks().Add(newChunk)) {
      return true;
    }
  }
  return false;
}

bool Matcher::RuleIntransitiveVerb_(
    std::shared_ptr<basic::NluContext> nluContext,
    const std::shared_ptr<basic::Chunk> &chunk) {
  if (chunk->GetTag() != basic::SyntaxTag::Type::kV ||
      basic::Manager::Get().GetGkb().GetGkbVerb().TiWeiZhun(
              chunk->GetStrFromSentence(nluContext->GetQuery())) !=
              basic::EntryVerb::TiWeiZhun::kNone) {
    return false;
  }

  auto npBefore = nluContext->GetChunks().GetFragmentBefore(chunk->GetOffset());
  if (nullptr == npBefore || !npBefore->ContainTag(basic::SyntaxTag::Type::kNp)) {
    return false;
  }

  while (true) {
    auto chunkBefore = nluContext->GetChunks().GetFragmentBefore(npBefore->GetOffset());
    if (nullptr != chunkBefore && chunkBefore->ContainTag(basic::SyntaxTag::Type::kNp)) {
      npBefore = chunkBefore;
    } else {
      break;
    }
  }

  basic::Chunk newChunk(
          basic::SyntaxTag::Type::kVp,
          npBefore->GetOffset(),
          chunk->GetEnd() - npBefore->GetOffset(),
          440);
  if (nluContext->GetChunks().Add(newChunk)) {
    return true;
  }
  return false;
}

void Matcher::AddAdvpDescDir_(std::shared_ptr<basic::NluContext> nluContext) {
  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetTag() == basic::SyntaxTag::Type::kAdvp) {
      AddAdvpDescDirForChunk_(nluContext, chunk);
    }
  }
}

void Matcher::AddAdvpDescDirForChunk_(
        std::shared_ptr<basic::NluContext> nluContext,
        std::shared_ptr<basic::Chunk> advp) {
  std::vector<std::pair<std::shared_ptr<basic::Segment>, basic::Chunk::DescDir>> adjs;
  for (auto &segment : nluContext->GetSegments().GetAll()) {
    if (segment->GetOffset() >= advp->GetOffset() &&
        segment->GetOffset() + segment->GetLen() <= advp->GetOffset() + advp->GetLen()) {
      if (segment->GetTag() == basic::PosTag::Type::kA) {
        adjs.push_back(std::make_pair(segment, basic::Chunk::kNone));
      }
    }
  }

  if (adjs.empty()) {
    return;
  } else if (adjs.size() == 1) {
    int descLeft=0;
    int descRight=0;
    int leftBound=-1;
    int rightBound=-1;
    AnalysisAdj_(
            nluContext,
            advp,
            adjs[0].first,
            descLeft,
            descRight,
            leftBound,
            rightBound);
    if (descLeft>0 &&
        descRight<0 &&
        leftBound>0) {
      advp->SetDescDir(basic::Chunk::kLeft);
      nluContext->GetChunks().Add(std::make_shared<basic::Chunk>(
              basic::SyntaxTag::Type::kV,
              leftBound,
              advp->GetEnd() - leftBound,
              450));
    } else if (descLeft<0 &&
        descRight>0 &&
        rightBound>0) {
      advp->SetDescDir(basic::Chunk::kRight);
      nluContext->GetChunks().Add(std::make_shared<basic::Chunk>(
              basic::SyntaxTag::Type::kNp,
              advp->GetOffset(),
              rightBound - advp->GetOffset(),
              451));
    } else if (-1==descLeft && -1==descRight) {
      nluContext->SetIsValid(false);
    }
  } else if (adjs.size() == 2) {
    int descLeft[2] = {0, 0};
    int descRight[2] = {0, 0};
    int leftBound[2] = {-1, -1};
    int rightBound[2] = {-1, -1};
    AnalysisAdj_(
            nluContext,
            advp,
            adjs[0].first,
            descLeft[0],
            descRight[0],
            leftBound[0],
            rightBound[0]);
    AnalysisAdj_(
            nluContext,
            advp,
            adjs[1].first,
            descLeft[1],
            descRight[1],
            leftBound[1],
            rightBound[1]);
    if (descLeft[0] > 0 &&
        descLeft[1] > 0 &&
        descRight[0] < 0 &&
        descRight[1] < 0) {
      advp->SetDescDir(basic::Chunk::kLeft);
      nluContext->GetChunks().Add(std::make_shared<basic::Chunk>(
              basic::SyntaxTag::Type::kV,
              leftBound[0],
              advp->GetEnd() - leftBound[0],
              452));
    } else if (descLeft[0] < 0 &&
        descLeft[1] < 0 &&
        descRight[0] > 0 &&
        descRight[1] > 0) {
      advp->SetDescDir(basic::Chunk::kRight);
      nluContext->GetChunks().Add(std::make_shared<basic::Chunk>(
              basic::SyntaxTag::Type::kV,
              advp->GetOffset(),
              rightBound[1] - advp->GetOffset(),
              453));
    } else if ((-1==descLeft[0] && -1==descRight[0]) ||
        (-1==descLeft[1] && -1==descRight[1])) {
      nluContext->SetIsValid(false);
    }
  }
}

void Matcher::AnalysisAdj_(
        std::shared_ptr<basic::NluContext> &nluContext,
        std::shared_ptr<basic::Chunk> advp,
        std::shared_ptr<basic::Segment> adj,
        int &descLeft,
        int &descRight,
        int &leftBound,
        int &rightBound) {
  descLeft=0;
  descRight=0;
  rightBound=0;

  auto segBefore = nluContext->GetSegments().GetFragmentBefore(advp->GetOffset());
  if (nullptr!=segBefore) {
    auto strSegBefore = segBefore->GetQuery(nluContext->GetQuery());
    if (segBefore->GetQuery(nluContext->GetQuery()) == L"得") {
      descLeft=1;
      descRight=-1;
      auto segBeforeBefore = nluContext->GetSegments().GetFragmentBefore(segBefore->GetOffset());
      if (segBeforeBefore != nullptr) {
        leftBound = segBeforeBefore->GetOffset();
      }
      return;
    } else if (segBefore->GetTags().size() != 1) {
      return;
    } else if (segBefore->GetTag() == basic::PosTag::Type::kV) {
      if (basic::Manager::Get().GetGkb().GetGkbVerb().IsDongjie(strSegBefore) ||
          basic::Manager::Get().GetGkb().GetGkbVerb().IsDongqu(strSegBefore)) {
        descLeft=1;
        leftBound = segBefore->GetOffset();
      } else {
        descLeft=-1;
      }
    } else {
      descLeft=-1;
    }
  } else {
    descLeft=-1;
    descRight=1;
  }

  auto segAfter = nluContext->GetChunks().GetFragmentAfter(advp->GetEnd());
  if (nullptr!=segAfter) {
    if (segAfter->GetQuery(nluContext->GetQuery()) == L"的") {
      descLeft=-1;
      descRight=1;
      auto segAfterAfter = nluContext->GetChunks().GetFragmentAfter(segAfter->GetEnd());
      if (segAfterAfter != nullptr) {
        rightBound = segAfterAfter->GetEnd();
      }
    }

    bool theRightTag=true;
    if (segAfter->GetTags().empty()) {
      theRightTag=false;
    } else {
      for (auto tag : segAfter->GetTags()) {
        if (tag != basic::SyntaxTag::Type::kNp &&
            tag != basic::SyntaxTag::Type::kQp &&
            !basic::SyntaxTag::Type::IsSpecial(tag)) {
          theRightTag=false;
          break;
        }
      }
    }

    if (theRightTag) {
      int dingyu = basic::Manager::Get().GetGkb().GetGkbAdj().Dingyu(adj->GetQuery(nluContext->GetQuery()));
      if (0==dingyu) {
        descRight=1;
        rightBound = segAfter->GetEnd();
      } else {
        descRight=-1;
      }
    } else {
      descRight=-1;
    }
  }
}

}}}
