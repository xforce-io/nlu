#pragma once

#include "public.h"
#include "analysis_component.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureSegments;
class FeatureNameEntity;

class AnalysisClause : public AnalysisComponent {
 public: 
  AnalysisClause(const std::wstring &clause);

  void Segment();

  void Dump(JsonType &jsonType);

 private:
  AnalysisClause *father_;

  std::wstring clause_;
  std::shared_ptr<basic::NluContext> nluContext_;
};

}}}
