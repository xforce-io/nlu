#include "../interface.h"

namespace xforce { namespace nlu { namespace charles {

bool Interface::ParseRaw(
    const std::vector<std::string> flags,
    std::shared_ptr<basic::NluContext> &nluContext) {
  nluContext->Reset(query, basic::Stage::kNone);
  for (auto &flag : flags) {
    if ("seg" == flag) {
      segmentor::Segmentor::Parse(nluContext);
    } else {
      return false;
    }
  }
  return true;
}

}}}