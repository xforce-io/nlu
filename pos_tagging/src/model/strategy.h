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
  virtual void Process(basic::NluContext &nluContext) = 0;

 protected:
  virtual void SetPos(
          std::shared_ptr<basic::Segment> &segment,
          basic::PosTag::Type posTag,
          uint32_t strategy);

  virtual void AddPos(
          std::shared_ptr<basic::Segment> &segment,
          basic::PosTag::Type posTag);
};

}}}
