#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class ProcessorSentence {
 public: 
  //@return : is analysisSentence modified 
  typedef bool (*Processor)(
      AnalysisContext &analysisContext,
      AnalysisSentence &analysisSentence);
};

}}}
