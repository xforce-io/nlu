#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisSentence;
class AnalysisClause;

class AnalysisContext {
 public:
  typedef std::vector<std::shared_ptr<AnalysisClause>> AnalysisClauses;

 public:
  AnalysisContext(const std::wstring &query); 

  void Dump(JsonType &jsonType);

  AnalysisSentence& GetAnalysisSentence() { return *analysisSentence_; }
  AnalysisClauses& GetAnalysisClauses() { return analysisClauses_; }

 private:
   std::shared_ptr<AnalysisSentence> analysisSentence_;
   AnalysisClauses analysisClauses_;
};

}}}
