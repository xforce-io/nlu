#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher;

class Chunker {
 public: 
  Chunker(); 

  bool Init(const xforce::JsonType &confJson);
  void Parse(basic::NluContext &nluContext);

  void Tini();

 private:


 private:
  Matcher *matcher_;
};

}}}
