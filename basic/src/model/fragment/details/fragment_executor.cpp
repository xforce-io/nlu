#include "../fragment_executor.h"
#include "../manager_fragment_set.h"
#include "../segment.h"
#include "../chunk.h"

namespace xforce { namespace nlu { namespace basic {

void FragmentExecutor::AddSegment(const Segment &segment) {
  managerFragmentSet_->Get<Segment>().Add(segment);
}

void FragmentExecutor::AddChunk(const Chunk &chunk) {
  managerFragmentSet_->Get<Chunk>().Add(chunk);
}

}}}
