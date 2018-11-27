#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class ProcessorContext {
 private:
  typedef std::vector<ProcessorSentence::Processor*> ProcessorSentences;
  typedef std::vector<ProcessorClause::Processor*> ProcessorClauses;

 public:
  ProcessorContext(); 

  ProcessorSentences& GetProcessorSentences() { return processorSentences_; }
  ProcessorClauses& GetProcessorClauses() { return processorClauses_; }

  //@return : is analysisContext modified 
  inline bool ProcessSentence(
      AnalysisContext &analysisContext,
      AnalysisSentence &analysisSentence);

  //@return : is analysisContext modified 
  inline bool ProcessClause(
      AnalysisContext &analysisContext,
      AnalysisClause &analysisClause);

  ~ProcessorContext();

  static ProcessorContext& Get() { return *processorContext_; }

 private: 
  ProcessorSentences processorSentences_; 
  ProcessorClauses processorClauses_;

  static ProcessorContext *processorContext_;
};

bool ProcessorContext::ProcessSentence(
    AnalysisContext &analysisContext,
    AnalysisSentence &analysisSentence) {
  bool modified = false;
  for (auto processor : processorSentences_) {
    if (processor(analysisContext, analysisSentence)) {
      modified = true;
    }
  }
  return modified;
}

bool ProcessorContext::ProcessClause(
    AnalysisContext &analysisContext,
    AnalysisClause &analysisClause) {
  bool modified = false;
  for (auto processor : processorClauses_) {
    if (processor(analysisContext, analysisSentence)) {
      modified = true;
    }
  }
  return modified;
}

}}}
