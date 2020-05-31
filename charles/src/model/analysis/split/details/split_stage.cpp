#include "../split_stage.h"
#include "../split_rule_mgr.h"
#include "../forbid_mgr.h"

namespace xforce { namespace nlu { namespace charles {

SplitStage::SplitStage(
        SplitRuleMgr &splitRuleMgr) :
  splitRuleMgr_(&splitRuleMgr),
  forbidMgr_(new ForbidMgr()),
  bornStage_(basic::Stage::kNone),
  curStage_(basic::Stage::kSegment),
  ruleIdx_(0),
  lastStage_(basic::Stage::kNone),
  lastRuleIdx_(0) {}

SplitStage::~SplitStage() {
  XFC_DELETE(forbidMgr_)
  XFC_DELETE(splitRuleMgr_)
}

void SplitStage::Process(std::shared_ptr<basic::NluContext> &nluContext) {
  switch (bornStage_) {
    case basic::Stage::kNone :
      segmentor::Segmentor::Parse(nluContext);
      pos::PosTagging::Tagging(nluContext);
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      semantic::Semantic::Parse(nluContext);
      break;
    case basic::Stage::kSegment :
      segmentor::Segmentor::Parse(nluContext);
      pos::PosTagging::Tagging(nluContext);
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      semantic::Semantic::Parse(nluContext);
      break;
    case basic::Stage::kPosTag :
      pos::PosTagging::Tagging(nluContext);
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      semantic::Semantic::Parse(nluContext);
      break;
    case basic::Stage::kChunk :
      chunker::Chunker::Parse(nluContext);
      syntax::Syntax::Parse(nluContext);
      semantic::Semantic::Parse(nluContext);
      break;
    case basic::Stage::kSyntax :
      syntax::Syntax::Parse(nluContext);
      semantic::Semantic::Parse(nluContext);
      break;
    case basic::Stage::kSemantic :
      semantic::Semantic::Parse(nluContext);
      break;
    default :
      break;
  }

  splitRuleMgr_->Adjust(*nluContext);
  ruleIdx_=0;
  while (!IsEnd()) {
    size_t curStageSize = splitRuleMgr_->GetRules()[curStage_]->size();
    if (ruleIdx_ < curStageSize) {
      return;
    } else {
      curStage_ = basic::Stage::GetNext(curStage_);
      ruleIdx_=0;
    }
  }
}

void SplitStage::Split(
        const std::shared_ptr<basic::NluContext> &nluContext,
        CollectionNluContext &nluContexts) {
  if (IsBegin() || IsEnd()) {
    return;
  }

  auto &rule = *((*(splitRuleMgr_->GetRules()[curStage_]))[ruleIdx_]);
  if (forbidMgr_->GlobalCheckRule(rule) &&
      forbidMgr_->PreCheckRule(rule)) { //pre check
    rule.Split(*this, nluContext, nluContexts);
    if (!forbidMgr_->PostCheckRule(rule)) { // post check
      nluContexts.Clear();
    } else if (nluContexts.NonEmpty()) {
      forbidMgr_->AddRule(rule);
    }
  }
  lastStage_ = curStage_;
  lastRuleIdx_ = ruleIdx_;
  NextStage();
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
  newStage->forbidMgr_ = forbidMgr_->Clone();
  newStage->bornStage_ = bornStage_;
  newStage->curStage_ = curStage_;
  newStage->ruleIdx_ = ruleIdx_;
  newStage->lastStage_ = lastStage_;
  newStage->lastRuleIdx_ = lastRuleIdx_;
  return newStage;
}

const Rule* SplitStage::GetLastRule() const {
  if (basic::Stage::kNone != lastStage_) {
    return (*(splitRuleMgr_->GetRules()[lastStage_]))[lastRuleIdx_];
  } else {
    return nullptr;
  }
}

}}}
