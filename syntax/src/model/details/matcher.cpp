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
                  *nluContext,
                  syntaxTag,
                  storageItem.GetOffset() + (*cur)->GetOffset(),
                  storageItem.GetContent().length(),
                  410);
          if (nluContext->Add(chunk)) {
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
                *nluContext,
                syntaxTag,
                storageItem.GetOffset(),
                storageItem.GetContent().length(),
                420);
        if (nluContext->Add(chunk)) {
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
    if (RuleIntransitiveVerb_(nluContext, chunk)) {
      touched = true;
    }
  }

  if (RuleContNp_(nluContext)) {
    touched = true;
  }

  if (RuleDongquQuxiang_(nluContext)) {
    touched = true;
  }
  return touched;
}

void Matcher::AppendixProcess_(std::shared_ptr<basic::NluContext> nluContext) {
  AddAdvpDescDir_(nluContext);
}

bool Matcher::RuleIntransitiveVerb_(
    std::shared_ptr<basic::NluContext> nluContext,
    const std::shared_ptr<basic::Chunk> &chunk) {
  if (chunk->GetTag() != basic::SyntaxTag::Type::kV ||
      !basic::Manager::Get().GetGkb().GetGkbVerb().IsArgNone(
              chunk->GetStrFromSentence(nluContext->GetQuery()))) {
    return false;
  }

  //strategy 0 : add VP flag to intransitive verb chunk
  basic::Chunk newVp(
          *nluContext,
          basic::SyntaxTag::Type::kVp,
          chunk->GetBegin(),
          chunk->GetLen(),
          440);
  nluContext->Add(newVp);

  //strategy 1
  auto npBefore = nluContext->GetChunks().GetFragmentBefore(chunk->GetOffset());
  if (nullptr == npBefore || !npBefore->ContainTag(basic::SyntaxTag::Type::kNp)) {
    return false;
  }

  auto npAfter = nluContext->GetChunks().GetFragmentAfter(chunk->GetEnd());
  if (nullptr == npAfter || !npAfter->ContainTag(basic::SyntaxTag::Type::kNp)) {
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

  basic::Chunk newNp(
          *nluContext,
          basic::SyntaxTag::Type::kNp,
          npBefore->GetOffset(),
          chunk->GetEnd() - npBefore->GetOffset(),
          441);

  basic::Chunk newContNp(
          *nluContext,
          basic::SyntaxTag::Type::kContNp,
          npBefore->GetOffset(),
          chunk->GetEnd() - npBefore->GetOffset(),
          442);
  if (nluContext->Add(newNp) ||
      nluContext->Add(newContNp)) {
    return true;
  }
  return false;
}

bool Matcher::RuleContNp_(std::shared_ptr<basic::NluContext> nluContext) {
  std::shared_ptr<basic::Chunk> tmpChunk = nullptr;
  size_t maxLen = 0;
  for (auto &chunk : nluContext->GetChunks().GetAll()) {
    if (chunk->GetOffset() == 0) {
      if (chunk->GetTag() == basic::SyntaxTag::Type::kContNp &&
          chunk->GetLen() > maxLen) {
        tmpChunk = chunk;
        maxLen = chunk->GetLen();
      }
    } else {
      break;
    }
  }

  if (nullptr==tmpChunk) {
    return false;
  }

  auto segment = nluContext->GetSegments().GetFragmentAfter(tmpChunk->GetEnd());
  if (nullptr==segment ||
      (segment->GetTag() != basic::PosTag::Type::kUndef &&
      segment->GetTag() != basic::PosTag::Type::kV) ) {
    basic::Chunk newNp(
            *nluContext,
            basic::SyntaxTag::Type::kNp,
            0,
            tmpChunk->GetEnd(),
            442);
    if (nluContext->Add(newNp)) {
      return true;
    }
  }
  return false;
}

bool Matcher::RuleDongquQuxiang_(std::shared_ptr<basic::NluContext> nluContext) {
  bool touched = false;
  auto cur = nluContext->GetChunks().Begin();
  std::vector<std::shared_ptr<basic::Chunk>> chunksToAdd;
  while (cur != nluContext->GetChunks().End()) {
    auto next = cur;
    ++next;

    std::shared_ptr<basic::NluContext> fragment;
    if (next != nluContext->GetChunks().End()) {
      if ((*cur)->ContainTag(basic::SyntaxTag::Type::kV) &&
          (*next)->ContainTag(basic::SyntaxTag::Type::kV) &&
          (*cur)->GetEnd() == (*next)->GetOffset()) {
        auto curSeg = (*cur)->FindSeg(*nluContext, basic::PosTag::Type::kV);
        auto nextSeg = (*next)->FindSeg(*nluContext, basic::PosTag::Type::kV);
        if (nullptr != curSeg &&
            nullptr != nextSeg &&
            basic::Manager::Get().GetGkb().GetGkbVerb().IsDongqu(curSeg->GetStrFromSentence(nluContext->GetQuery())) &&
            basic::Manager::Get().GetGkb().GetGkbVerb().IsQuxiang(nextSeg->GetStrFromSentence(nluContext->GetQuery()))) {
          chunksToAdd.push_back(std::make_shared<basic::Chunk>(
                  *nluContext,
                  basic::SyntaxTag::Type::kV,
                  (*cur)->GetOffset(),
                  (*cur)->GetLen() + (*next)->GetLen(),
                  443));
          touched = true;
        }
      }
    } else {
      break;
    }
    cur = next;
  }

  for (auto &chunkToAdd : chunksToAdd) {
    nluContext->Add(chunkToAdd);
  }
  return touched;
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
      if (segment->GetTag() == basic::PosTag::Type::kA ||
          segment->GetTag() == basic::PosTag::Type::kB ||
          segment->GetTag() == basic::PosTag::Type::kZ) {
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
    basic::SyntaxTag::Type::Val resTag;
    AnalysisAdj_(
            nluContext,
            advp,
            adjs[0].first,
            descLeft,
            descRight,
            leftBound,
            rightBound,
            resTag);
    if (descLeft>0 &&
        descRight<0 &&
        leftBound>0) {
      advp->SetDescDir(basic::Chunk::kLeft);
      nluContext->Add(basic::Chunk(
              *nluContext,
              resTag,
              leftBound,
              advp->GetEnd() - leftBound,
              450));
    } else if (descLeft<0 &&
        descRight>0 &&
        rightBound>0) {
      advp->SetDescDir(basic::Chunk::kRight);
      nluContext->Add(basic::Chunk(
              *nluContext,
              resTag,
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
    basic::SyntaxTag::Type::Val resTag[2];
    AnalysisAdj_(
            nluContext,
            advp,
            adjs[0].first,
            descLeft[0],
            descRight[0],
            leftBound[0],
            rightBound[0],
            resTag[0]);
    AnalysisAdj_(
            nluContext,
            advp,
            adjs[1].first,
            descLeft[1],
            descRight[1],
            leftBound[1],
            rightBound[1],
            resTag[1]);
    if (descLeft[0] > 0 &&
        descLeft[1] > 0 &&
        descRight[0] < 0 &&
        descRight[1] < 0) {
      advp->SetDescDir(basic::Chunk::kLeft);
      nluContext->Add(basic::Chunk(
              *nluContext,
              resTag[0],
              leftBound[0],
              advp->GetEnd() - leftBound[0],
              452));
    } else if (descLeft[0] < 0 &&
        descLeft[1] < 0 &&
        descRight[0] > 0 &&
        descRight[1] > 0) {
      advp->SetDescDir(basic::Chunk::kRight);
      nluContext->Add(basic::Chunk(
              *nluContext,
              resTag[1],
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
        int &rightBound,
        basic::SyntaxTag::Type::Val &resTag) {
  descLeft=0;
  descRight=0;
  rightBound=0;

  auto segBefore = nluContext->GetSegments().GetFragmentBefore(advp->GetOffset());
  if (nullptr!=segBefore) {
    auto strSegBefore = segBefore->GetQuery(nluContext->GetQuery());
    if (L"得"==strSegBefore || L"不"==strSegBefore) {
      descLeft=1;
      descRight=-1;
      auto segBeforeBefore = nluContext->GetSegments().GetFragmentBefore(segBefore->GetOffset());
      if (segBeforeBefore != nullptr) {
        leftBound = segBeforeBefore->GetOffset();
      }
      resTag = basic::SyntaxTag::Type::kVp;
      return;
    } else if (segBefore->GetTags().size() != 1) {
      return;
    } else if (segBefore->GetTag() == basic::PosTag::Type::kV) {
      if (basic::Manager::Get().GetGkb().GetGkbVerb().IsDongjie(strSegBefore) ||
          basic::Manager::Get().GetGkb().GetGkbVerb().IsDongqu(strSegBefore)) {
        descLeft=1;
        leftBound = segBefore->GetOffset();
        resTag = basic::SyntaxTag::Type::kVp;
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
      resTag = basic::SyntaxTag::Type::kNp;
    } else {
      std::wstring adjStr = adj->GetQuery(nluContext->GetQuery());

      bool theRightTag = true;
      if (segAfter->GetTags().empty()) {
        theRightTag = false;
      } else {
        for (auto tag : segAfter->GetTags()) {
          if (tag == basic::SyntaxTag::Type::kContNp) {
            resTag = basic::SyntaxTag::Type::kNp;
          } else if (!basic::SyntaxTag::Type::IsSpecial(tag)) {
            if (tag != basic::SyntaxTag::Type::kNp &&
                tag != basic::SyntaxTag::Type::kQp &&
                tag != basic::SyntaxTag::Type::kV &&
                tag != basic::SyntaxTag::Type::kVp) {
              theRightTag = false;
              break;
            } else {
              resTag = tag;
            }
          }
        }
      }

      if (theRightTag) {
        int ret;
        if (basic::SyntaxTag::Type::kNp == resTag ||
            basic::SyntaxTag::Type::kQp == resTag) {
          ret = basic::Manager::Get().GetGkb().GetGkbAdj().Dingyu(adjStr);
        } else if (basic::SyntaxTag::Type::kV == resTag ||
            basic::SyntaxTag::Type::kVp == resTag) {
          ret = basic::Manager::Get().GetGkb().GetGkbAdj().Zhuangyu(adjStr);
        } else {
          ret = -1;
        }

        if (0==ret) {
          descRight = 1;
          rightBound = segAfter->GetEnd();
        } else {
          descRight = -1;
        }
      } else {
        descRight = -1;
      }
    }
  }
}

}}}
