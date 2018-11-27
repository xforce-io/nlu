#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureSegments;
class FeatureNameEntity;

class AnalysisClause : public AnalysisComponent {
 public: 
  AnalysisClause(const std::wstring &clause);

  void Segment();

 private: 
  std::wstring clause_;

  std::shared_ptr<FeatureSegments> featureSegments_;  
  std::vector<std::shared_ptr<FeatureNameEntity>> featureNameEntities_;
};

}}}
