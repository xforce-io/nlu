#pragma once

#include "../public.h"
#include "strategy.h"

namespace xforce { namespace nlu { namespace pos {

class WindowStatistics;

class StrategyWindowStatistics : public Strategy {
 public:
  StrategyWindowStatistics();
  virtual ~StrategyWindowStatistics();

  bool Init();
  void Process(basic::NluContext &nluContext);

 protected:
  virtual void SetPos(
          basic::Segment &segment,
          basic::PosTag::Type::Val posTag,
          uint32_t strategy);

 private:
  WindowStatistics *windowStatistics_;
};

}}}
