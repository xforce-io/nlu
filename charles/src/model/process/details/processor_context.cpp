#include "../processor_context.h"

namespace xforce { namespace nlu { namespace charles {

ProcessorContext* ProcessorContext::processorContext_ = new ProcessorContext();

ProcessorContext::ProcessorContext() {
  processorSentences_.push_back(ProcessorClause::Segment);
}

ProcessorContext::~ProcessorContext() {
  for (auto iter = processorSentences_.begin(); iter != processorSentences_.end(); ++iter) {
    XFC_DELETE(*iter)
  }

  for (auto iter = processorClauses_.begin(); iter != processorClauses_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
}

}}}
