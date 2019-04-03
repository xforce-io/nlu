#pragma once

#include "fragment.h"
#include "fragment_instruction.h"

namespace xforce { namespace nlu { namespace basic {

class Segment;
class Chunk;
class ManagerFragmentSet;

class FragmentExecutor {
 public:
  typedef std::vector<FragmentInstruction> FragmentInstructions;

 public:
  void AddSegment(const Segment &segment);
  void AddChunk(const Chunk &chunk);

 private:
  ManagerFragmentSet *managerFragmentSet_;
  FragmentInstructions fragmentInstructions_;
};

}}}
