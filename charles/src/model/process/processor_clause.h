#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisContext;
class AnalysisClause;

class ProcessorClause {
 public:
  //@return : is analysisContext modified 
  typedef bool (*Processor)(
      AnalysisContext &analysisContext,
      AnalysisClause &analysisClause);

 public: 
  inline static bool Segment(
      AnalysisContext &analysisContext,
      AnalysisClause &analysisClause); 
};

}}}

#include "../analysis/analysis_context.h"
#include "../analysis/analysis_clause.h"

namespace xforce { namespace nlu { namespace charles {

bool ProcessorClause::Segment(
    AnalysisContext &analysisContext,
    AnalysisClause &analysisClause) {
  analysisClause.Segment();
  return false;
}

}}}
