#pragma once

#include "public.h"
#include "model/strategy.h"

namespace xforce { namespace nlu { namespace pos {

class PosTagging {
 public:
  PosTagging();
  virtual ~PosTagging();

  void Process(basic::NluContext &nluContext);

 public:
  static void Tagging(basic::NluContext &nluContext);

 private:
  void SetPosCtbFromPos_(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments);

 private:
  std::vector<Strategy*> strategies_;

  static PosTagging posTagging_;
};

}}}
