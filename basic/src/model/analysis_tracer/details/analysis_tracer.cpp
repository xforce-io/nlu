#include "../analysis_tracer.h"

namespace xforce { namespace nlu { namespace basic {

void AnalysisTracer::AddEvent(
        const std::string &key,
        const std::string &event) {
  Get()->Add(key, event);
  NOTICE("add_event[" << key << "|" << event << "]");
}

void AnalysisTracer::AddEvent(
        const std::wstring &key,
        const std::string &event) {
  Get()->Add(*(StrHelper::Wstr2Str(key)), event);
  NOTICE("add_event[" << key << "|" << event << "]");
}

void AnalysisTracer::AddEvent(
        const std::string &key,
        const std::wstring &event) {
  Get()->Add(key, event);
  NOTICE("add_event[" << key << "|" << event << "]");
}

void AnalysisTracer::AddEvent(
        const std::wstring &key,
        const std::wstring &event) {
  Get()->Add(*(StrHelper::Wstr2Str(key)), event);
  NOTICE("add_event[" << key << "|" << event << "]");
}

void AnalysisTracer::AddEvent(
        const std::string &key,
        const JsonType &event) {
  Get()->Add(key, event);
  NOTICE("add_event[" << key << "|" << event << "]");
}

void AnalysisTracer::AddEvent(
        const std::wstring &key,
        const JsonType &event) {
  Get()->Add(*(StrHelper::Wstr2Str(key)), event);
  NOTICE("add_event[" << key << "|" << event << "]");
}

AnalysisTracer* AnalysisTracer::Get() {
  auto analysisTracer = (AnalysisTracer*)Tracer::threadPrivacy_->Get(kNoAnalysisTracer);
  if (nullptr == analysisTracer) {
    auto newAnalysisTracer = new AnalysisTracer();
    analysisTracer = Tracer::threadPrivacy_->Get(
            kNoAnalysisTracer,
            newAnalysisTracer,
            nullptr);
    if (nullptr == analysisTracer) {
      XFC_DELETE(newAnalysisTracer)
      return nullptr;
    }
  }
  return analysisTracer;
}

}}}
