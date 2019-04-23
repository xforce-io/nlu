#include "../function_post_np.h"

namespace xforce { namespace nlu { namespace chunker {

void FunctionPostNp::Process(
        const milkie::StorageItem &storageItem,
        basic::NluContext &nluContext) {
  nluContext.GetChunkSeps().Add(
          std::make_shared<basic::ChunkSep>(
                  storageItem.GetOffset() + storageItem.GetContent().length()));
}

bool FunctionPostNp::ProcessModifier_() {

}

}}}
