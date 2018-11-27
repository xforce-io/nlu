#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

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

bool ProcessorClause::Segment(
    AnalysisContext &analysisContext,
    AnalysisClause &analysisClause) {
  analysisClause.Segment();
}

}}}
