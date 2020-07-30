#pragma once

#include "../public.h"
#include "rule.h"

namespace xforce { namespace nlu { namespace charles {

class SplitRuleMgr;
class ForbidMgr;

class SplitStage {
 public:
  SplitStage(SplitRuleMgr &splitRuleMgr);
  virtual ~SplitStage();

  void Process(std::shared_ptr<basic::NluContext> &nluContext);
  void Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          CollectionNluContext &nluContexts);

  inline void SetBornStage(basic::Stage::Val stage);
  inline void SetCurStage(basic::Stage::Val stage);
  inline void SetRuleIdx(size_t ruleIdx);

  inline void AddForbidInterval(size_t offset, size_t len);
  bool PrevStage();
  bool NextStage();
  SplitStage* Clone() const;

  inline bool IsBegin() const;
  inline bool IsEnd() const;

  basic::Stage::Val GetBornStage() const { return bornStage_; }
  basic::Stage::Val GetCurStage() const { return curStage_; }
  size_t GetRuleIdx() const { return ruleIdx_; };
  basic::Stage::Val GetLastStage() const { return lastStage_; }
  size_t GetLastRuleIdx() const { return lastRuleIdx_; }

  const Rule* GetLastRule() const;

 private:
  SplitRuleMgr *splitRuleMgr_;
  ForbidMgr *forbidMgr_;

  basic::Stage::Val bornStage_;
  basic::Stage::Val curStage_;
  size_t ruleIdx_;

  basic::Stage::Val lastStage_;
  size_t lastRuleIdx_;

  std::vector<std::pair<size_t, size_t>> forbidIntervals_;
};

void SplitStage::SetBornStage(basic::Stage::Val stage) {
  bornStage_ = stage;
}

void SplitStage::SetCurStage(basic::Stage::Val stage) {
  curStage_ = stage;
}

void SplitStage::SetRuleIdx(size_t ruleIdx) {
  ruleIdx_ = ruleIdx;
}

void SplitStage::AddForbidInterval(size_t offset, size_t len) {
  forbidIntervals_.push_back(std::make_pair(offset, len));
}

bool SplitStage::IsBegin() const {
  return basic::Stage::kNone == curStage_;
}

bool SplitStage::IsEnd() const {
  return basic::Stage::kEnd == curStage_;
}

}}}
