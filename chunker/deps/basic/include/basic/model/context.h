#pragma once

#include "../public.h"
#include "fragment/fragment_set.hpp"
#include "segment.h"
#include "name_entity.h"

namespace xforce { namespace nlu { namespace basic {

class Context {
 public:
  Context(const std::wstring &query);
  virtual ~Context();

  const FragmentSet<Segment>& GetSegments() const { return *segments_; }
  FragmentSet<Segment>& GetSegments() { return *segments_; }
  const FragmentSet<NameEntity>& GetNameEntities() const { return *nameEntities_; }
  FragmentSet<NameEntity>& GetNameEntities() { return *nameEntities_; }

 private:
  std::wstring query_;
  FragmentSet<Segment> *segments_;
  FragmentSet<NameEntity> *nameEntities_;
};

}}}
