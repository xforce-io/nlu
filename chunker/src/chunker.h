#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher;

class Chunker {
 public:
  Chunker();
  virtual ~Chunker();

  bool Init();
  void Process(basic::NluContext &nluContext);

 public: 
  static bool Init(const xforce::JsonType &confJson);
  static void Parse(basic::NluContext &nluContext);
  static void Tini() {}

 private:
  Matcher *matcher_;

  static Chunker chunker_;
};

}}}
