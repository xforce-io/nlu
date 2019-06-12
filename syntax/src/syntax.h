#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace syntax {

class Matcher;

class Syntax {
 public:
  Syntax();
  virtual ~Syntax();

  bool Init();
  void Process(basic::NluContext &nluContext);

 public: 
  static bool Init(const xforce::JsonType &confJson);
  static void Parse(std::shared_ptr<basic::NluContext> nluContext);
  static void Tini() {}

 private:
  Matcher *matcher_;

  static Syntax syntax_;
};

}}}
