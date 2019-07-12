#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisContext;
class AnalysisClause;
class AnalysisSentence;

class ProcessorClause {
 public:
  //@return : is analysisSentence modified
  typedef bool (*Processor)(
          AnalysisContext &analysisContext,
          AnalysisSentence &analysisSentence);

 public:
  inline static bool Process(
      AnalysisContext &analysisContext,
      AnalysisClause &analysisClause); 
};

}}}
