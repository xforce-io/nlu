#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace ner {

class Recognizer {
 public:
  Recognizer() {}
  virtual ~Recognizer() {}

 public:
  virtual bool Init() { return true; }
  virtual void Process(std::shared_ptr<basic::NluContext> nluContext) = 0;
};

}}}