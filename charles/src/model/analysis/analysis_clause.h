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
  std::wstring clause_;

  basic::FragmentSet featureSegments_;
  basic::FragmentSet featureNameEntities_;
};

}}}
