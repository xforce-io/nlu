#pragma once

#include "public.h"
#include "analysis_component.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause;  

class AnalysisSentence : public AnalysisComponent {
 public:
  AnalysisSentence(
      const std::wstring &sentence, 
      const std::vector<std::shared_ptr<AnalysisClause>> &analysisClauses);

  void Dump(JsonType &jsonType);

 private: 
  std::wstring sentence_;
  const std::vector<std::shared_ptr<AnalysisClause>> *analysisClauses_;
};

}}}
