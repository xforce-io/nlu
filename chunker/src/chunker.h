#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher;

class Chunker {
 public: 
  static bool Init(const xforce::JsonType &confJson);
  static void Parse(basic::NluContext &nluContext);

  static void Tini();

 private:
  static Matcher *matcher_;
};

}}}
