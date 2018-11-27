#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause;  

class AnalysisSentence : public AnalysisComponent {
 public:
  AnalysisSentence(
      const std::wstring &sentence, 
      const std::vector<std::shared_ptr<AnalysisClause>> &analysisClauses);

 private: 
  std::wstring sentence_;
  const std::vector<std::shared_ptr<AnalysisClause>> *analysisClauses_;
};

}}}
