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
  static void Tagging(std::shared_ptr<basic::NluContext> nluContext);
  static void Tini();

 private:
  void PostProcess_(basic::NluContext &nluContext);

 private:
  std::vector<Strategy*> strategies_;

  static PosTagging posTagging_;
};

}}}
