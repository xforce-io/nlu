#include "../pos_tagging.h"
#include "../model/strategy_uniq.h"

namespace xforce { namespace nlu { namespace pos {

PosTagging::PosTagging() {
  strategies_.push_back(new StrategyUniq());
}

PosTagging::~PosTagging() {
  for (auto *strategy : strategies_) {
    delete strategy;
  }
}

void PosTagging::Process(basic::NluContext &nluContext) {
  for (auto &strategy : strategies_) {
    strategy->Process(nluContext);
  }
}

void PosTagging::Tagging(basic::NluContext &nluContext) {
  posTagging_.Process(nluContext);
}

void PosTagging::SetPosCtbFromPos_(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments) {
  for (size_t i=0; i < segments.Size(); ++i) {
    auto &segment = segments[i];
    auto pos = segment->GetPosTag();
    if (basic::PosTag::kN == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kNn);
    } else if (basic::PosTag::kT == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kNt);
    } else if (basic::PosTag::kS == pos ||
        basic::PosTag::kF == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kLc);
    } else if (basic::PosTag::kM == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kCd);
    } else if (basic::PosTag::kQ == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kM);
    } else if (basic::PosTag::kR == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kPn);
    } else if (basic::PosTag::kV == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kVv);
    } else if (basic::PosTag::kA == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kJj);
    } else if (basic::PosTag::kB == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kJj);
    } else if (basic::PosTag::kD == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kAd);
    } else if (basic::PosTag::kP == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kP);
    } else if (basic::PosTag::kC == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kCc);
    } else if (basic::PosTag::kW == pos) {
      segment->SetPosCtbTag(basic::PosCtbTag::kPu);
    }
  }
}

}}}
