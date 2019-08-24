#include "../split_stage.h"
#include "../split_rule_mgr.h"

namespace xforce { namespace nlu { namespace charles {

SplitStage::SplitStage(
        SplitRuleMgr &splitRuleMgr) :
  splitRuleMgr_(&splitRuleMgr),
  bornStage_(basic::Stage::kNone),
  curStage_(basic::Stage::kSyntax),
  lastStage_(basic::Stage::kNone),
  ruleIdx_(0) {}

SplitStage::~SplitStage() {
  XFC_DELETE(splitRuleMgr_)
}

void SplitStage::Process(std::shared_ptr<basic::NluContext> &nluContext) {
  switch (bornStage_) {
    case basic::Stage::kNone :
      segmentor::Segmentor::Parse(nluContext);
      pos::PosTagging::Tagging(nluContext);
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      break;
    case basic::Stage::kSegment :
      segmentor::Segmentor::Parse(nluContext);
      pos::PosTagging::Tagging(nluContext);
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      break;
    case basic::Stage::kPosTag :
      pos::PosTagging::Tagging(nluContext);
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      break;
    case basic::Stage::kChunk :
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      break;
    case basic::Stage::kSyntax :
      syntax::Syntax::Parse(nluContext);
      break;
    default :
      break;
  }

  splitRuleMgr_->Adjust(*nluContext);
  while (!IsBegin()) {
    size_t curStageSize = splitRuleMgr_->GetRules()[curStage_]->size();
    if (ruleIdx_ < curStageSize) {
      return;
    } else if (curStageSize != 0) {
      ruleIdx_ = curStageSize-1;
      return;
    } else {
      curStage_ = basic::Stage::GetPrev(curStage_);
      ruleIdx_=0;
    }
  }
}

bool SplitStage::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        std::vector<std::shared_ptr<basic::NluContext>> &nluContexts) {
  if (IsBegin() || IsEnd()) {
    return false;
  }

  auto rules = *(splitRuleMgr_->GetRules()[curStage_]);
  auto *rule = rules[ruleIdx_];
  bool ret = rule->Split(nluContext, nluContexts);
  lastStage_ = curStage_;
  PrevStage();
  return ret;
}

bool SplitStage::PrevStage() {
  if (IsBegin()) {
    return false;
  }

  ++ruleIdx_;

  while (true) {
    size_t curStageSize = splitRuleMgr_->GetRules()[curStage_]->size();
    if (curStageSize == ruleIdx_) {
      curStage_ = basic::Stage::GetPrev(curStage_);
      ruleIdx_ = 0;
      if (IsBegin()) {
        return false;
      }
    } else {
      break;
    }
  }
  return true;
}

bool SplitStage::NextStage() {
  if (IsEnd()) {
    return false;
  }

  ++ruleIdx_;

  while (true) {
    size_t curStageSize = splitRuleMgr_->GetRules()[curStage_]->size();
    if (curStageSize == ruleIdx_) {
      curStage_ = basic::Stage::GetNext(curStage_);
      ruleIdx_ = 0;
      if (IsEnd()) {
        return false;
      }
    } else {
      break;
    }
  }
  return true;
}

SplitStage* SplitStage::Clone() const {
  auto *newStage = new SplitStage(*splitRuleMgr_);
  newStage->splitRuleMgr_ = splitRuleMgr_->Clone();
  newStage->bornStage_ = bornStage_;
  newStage->curStage_ = curStage_;
  newStage->lastStage_ = lastStage_;
  newStage->ruleIdx_ = ruleIdx_;
  return newStage;
}

}}}
