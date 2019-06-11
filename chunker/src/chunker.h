#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher;

class Chunker {
 public:
  Chunker();
  virtual ~Chunker();

  bool Init();
  void Process(std::shared_ptr<basic::NluContext> nluContext);

 public: 
  static bool Init(const xforce::JsonType &confJson);
  static void Parse(std::shared_ptr<basic::NluContext> nluContext);
  static void Tini() {}

 private:
  Matcher *matcher_;

  static Chunker chunker_;
};

}}}
