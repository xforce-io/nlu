#include "../parser_mid_conj.h"

namespace xforce { namespace nlu { namespace semantic {

bool ParserMidConj::Filter_(basic::NluContext &nluContext) {
  conjs_.clear();
  for (auto &segment : nluContext.Get<basic::Segment>().GetAll()) {
    bool prev, mid, post;
    if (segment->GetTag() == basic::PosTag::Type::kC &&
        basic::Manager::Get().GetGkb().GetGkbConj().Pos(
                segment->GetQuery(nluContext.GetQuery()), prev, mid, post)) {
      if (mid) {
        conjs_.push_back(segment);
      }
    }
  }
  return !conjs_.empty();
}

void ParserMidConj::Process_(basic::NluContext &nluContext) {
  for (auto &conj : conjs_) {
    if (ProcessFeature_<basic::SemanticUnitEntity>(nluContext, conj) ||
        ProcessFeature_<basic::Chunk>(nluContext, conj) ||
        ProcessFeature_<basic::Segment>(nluContext, conj)) {
      continue;
    }
  }
}

template <typename FragmentType>
bool ParserMidConj::ProcessFeature_(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> &conj) {
  std::vector<std::shared_ptr<FragmentType>> before;
  std::vector<std::shared_ptr<FragmentType>> after;
  nluContext.GetFragmentBefore<FragmentType>(conj->GetOffset(), before);
  nluContext.GetFragmentAfter<FragmentType>(conj->GetEnd(), after);

  ssize_t minDist = SSIZE_MAX;
  std::shared_ptr<FragmentType> minBefore;
  std::shared_ptr<FragmentType> minAfter;
  for (auto &beforeItem : before) {
    for (auto &afterItem : after) {
      ssize_t dist = beforeItem->Distance(*afterItem);
      if (dist < 0) {
        continue;
      }

      if (dist < minDist) {
        minDist = dist;
        minBefore = beforeItem;
        minAfter = afterItem;
      }
    }
  }

  if (minDist != SSIZE_MAX) {
    std::shared_ptr<basic::Chunk> newChunk = std::make_shared<basic::Chunk>(
            nluContext,
            basic::SyntaxTag::Type::kNp,
            minBefore->GetOffset(),
            minAfter->GetEnd() - minBefore->GetOffset(),
            600);
    nluContext.Add(newChunk);
    return true;
  }
  return false;
}

}}}
