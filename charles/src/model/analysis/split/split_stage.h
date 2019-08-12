#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class SplitRuleMgr;

class SplitStage {
 public:
  SplitStage(const SplitRuleMgr &splitRuleMgr);

  void Process(std::shared_ptr<basic::NluContext> &nluContext);
  bool Split(
          const std::shared_ptr<basic::NluContext> &nluContext,
          std::vector<std::shared_ptr<basic::NluContext>> &nluContexts);

  bool PrevStage();
  bool NextStage();
  SplitStage* Clone() const;

  inline bool IsBegin() const;
  inline bool IsEnd() const;

  basic::Stage::Val GetBornStage() const { return bornStage_; }
  basic::Stage::Val GetCurStage() const { return curStage_; }

 private:
  const SplitRuleMgr *splitRuleMgr_;
  basic::Stage::Val bornStage_;
  basic::Stage::Val curStage_;
  size_t ruleIdx_;
};

bool SplitStage::IsBegin() const {
  return basic::Stage::kNone == curStage_;
}

bool SplitStage::IsEnd() const {
  return basic::Stage::kEnd == curStage_;
}

}}}
