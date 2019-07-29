#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class Charles {
 public:
  Charles();
  virtual ~Charles();

  bool Init();
  void Process(std::shared_ptr<basic::NluContext> nluContext);

 public:
  static bool Init(const xforce::JsonType &confJson);
  static void Parse(std::shared_ptr<basic::NluContext> nluContext);
  static void Tini() {}

 private:
  static Charles charles_;
};

}}}
