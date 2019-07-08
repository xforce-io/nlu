#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisContext;
class AnalysisClause;

class ProcessorClause {
 public:
  inline static bool Process(
      AnalysisContext &analysisContext,
      AnalysisClause &analysisClause); 
};

}}}
