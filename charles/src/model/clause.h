#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class FeatureSegment;  
class FeatureNameEntity;

class Clause {
 private:
  typedef std::list<FeatureNameEntity*> FeatureNameEntities; 

 public:
  Clause();

  void Segment(); 

  virtual ~Clause();

 private:
  std::wstring clause_;

  FeatureSegment *featureSegment_;
  FeatureNameEntities featureNameEntities_;
};

}}}
