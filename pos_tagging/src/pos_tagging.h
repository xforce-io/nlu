#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace pos {

class Strategy;  

class PosTagging {
 public:
  PosTagging();
  virtual ~PosTagging();

  bool Init();
  void Process(basic::NluContext &nluContext);

 public:
  static bool Init(const xforce::JsonType &confPos);
  static void Tagging(basic::NluContext &nluContext);
  static void Tini();

 private:
  void SetPosCtbFromPos_(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments);

 private:
  std::vector<Strategy*> strategies_;

  static PosTagging posTagging_;
};

}}}
