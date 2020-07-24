#include "../strategy_verb_before_aux.h"

namespace xforce { namespace nlu { namespace pos {

void StrategyVerbBeforeAux::Process(xforce::nlu::basic::NluContext &nluContext) {
  Strategy::Process(nluContext);

  std::shared_ptr<basic::Segment> posAux;
  std::shared_ptr<basic::Segment> posVerb;
  for (auto &segment : nluContext.Get<basic::Segment>().GetAll()) {
    if (segment->GetTag() == basic::PosTag::Type::kU) {
      auto &segStr = segment->GetStrFromSentence(nluContext.GetQuery());
      if (segStr == L"了") {
        posAux = segment;
        break;
      }
    } else if (segment->ContainTag(basic::PosTag::Type::kV)) {
      if (posVerb != nullptr) {
        return;
      } else {
        posVerb = segment;
      }
    }
  }

  if (posAux == nullptr || posVerb == nullptr || posVerb->GetTags().size() == 1) {
    return;
  }

  posVerb->SetTag(basic::PosTag::Type::kV);
}

}}}