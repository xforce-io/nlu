#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace ner {

class Ner {
 public:
  Ner();
  virtual ~Ner();

  bool Init();
  void Process(std::shared_ptr<basic::NluContext> nluContext);

 public: 
  static bool Init(const xforce::JsonType &confJson);
  static void Parse(std::shared_ptr<basic::NluContext> nluContext);

  static void Tini();
};

}}}
