#include "../processor_context.h"

namespace xforce { namespace nlu { namespace charles {

ProcessorContext* ProcessorContext::processorContext_ = new ProcessorContext();

ProcessorContext::ProcessorContext() {
}

ProcessorContext::~ProcessorContext() {
}

}}}
