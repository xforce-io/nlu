#pragma once

#include "../public.h"
#include "recognizer.h"

namespace xforce { namespace nlu { namespace ner {

class RecognizerTime : public Recognizer {
 private:
  static const std::wstring kNerTimeStoragePrefix;

 public:
  RecognizerTime();
  virtual ~RecognizerTime() {}

 public:
  bool Init();
  void Process(std::shared_ptr<basic::NluContext> nluContext);

 protected:
  static int MatcherCb_(
      const StorageKey &key, 
      const std::shared_ptr<StorageVal> &val,
      std::shared_ptr<basic::NluContext> nluContext);

 private:
  milkie::Matcher *matcher_; 
};

}}}
