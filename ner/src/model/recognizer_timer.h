#pragma once

#include "../public.h"
#include "recognizer.h"

namespace xforce { namespace nlu { namespace ner {

class RecognizerTimer : public Recognizer {
 public:
  RecognizerTimer();
  virtual ~RecognizerTimer() {}

 public:
  void Process(std::shared_ptr<basic::NluContext> nluContext);
};

}}}