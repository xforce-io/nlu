#include "../analysis_tracer.h"

namespace xforce { namespace nlu { namespace basic {

void AnalysisTracer::AddEvent(const std::string &event) {
  Get()->Add("event", event);
}

void AnalysisTracer::AddEvent(const std::wstring &event) {
  Get()->Add("event", event);
}

void AnalysisTracer::AddEvent(const JsonType &event) {
  Get()->Add("event", event);
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
