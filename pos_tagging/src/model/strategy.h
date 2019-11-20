#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace pos {

class Strategy {
 public:
  static const uint32_t kStrategyUniq = 1; 
  static const uint32_t kStrategyWindowStatistics = 2; 
  static const uint32_t kStrategyContextInfer = 3;
  static const uint32_t kStrategyOther = 0;

 public:
  Strategy() {}
  virtual ~Strategy() {}

  virtual bool Init() { return true; }
  virtual void Process(basic::NluContext &nluContext);

 protected:
  virtual void SetPos(
          basic::Segment &segment,
          basic::PosTag::Type::Val posTag,
          uint32_t strategy);

  virtual void AddPos(
          basic::Segment &segment,
          basic::PosTag::Type::Val posTag);

 protected:
  basic::NluContext *nluContext_;
};

}}}
