#pragma once

#include "../../public.h"

#include "fragment.h"
#include "fragment_set.hpp"

namespace xforce { namespace nlu { namespace basic {

class ChunkSep : public Fragment {
 public:
  typedef Fragment Super;
  typedef FragmentSet<ChunkSep> Set;

 public:
  inline ChunkSep();
  inline ChunkSep(size_t offset);
  inline ChunkSep(const ChunkSep &other);
  virtual ~ChunkSep() {}

  Fragment::Category GetCategory() const { return kChunkSep; }

  void Dump(JsonType &jsonType) const;
};

ChunkSep::ChunkSep() :
  Fragment(-1, -1) {}

ChunkSep::ChunkSep(size_t offset) :
  Fragment(offset, 0) {}

ChunkSep::ChunkSep(const ChunkSep &other) :
    Super(other) {}

}}}

