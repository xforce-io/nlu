#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace basic {

class AnalysisTracer : public Tracer {
 private:
  static const size_t kNoAnalysisTracer = 1;

 public:
  void AddEvent(const std::string &key, const std::string &event);
  void AddEvent(const std::string &key, const std::wstring &event);
  void AddEvent(const std::string &key, const JsonType &event);

 public:
  static AnalysisTracer* Get();
};

}}}
