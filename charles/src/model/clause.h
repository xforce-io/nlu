#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureSegments;
class FeatureNameEntity;

class Clause {
 private:
  typedef std::list<FeatureNameEntity*> FeatureNameEntities; 

 public:
  Clause(const std::wstring &clause);

  void Segment(); 

  virtual ~Clause();

 private:
  std::wstring clause_;

  FeatureSegments *featureSegments_;
  FeatureNameEntities featureNameEntities_;
};

}}}
