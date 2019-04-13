#include "../pos_tagging.h"
#include "../conf/conf.h"
#include "../model/strategy_uniq.h"
#include "../model/strategy_window_statistics.h"

namespace xforce { namespace nlu { namespace pos {

PosTagging PosTagging::posTagging_;

PosTagging::PosTagging() {
  strategies_.push_back(new StrategyUniq());
  strategies_.push_back(new StrategyWindowStatistics());
}

PosTagging::~PosTagging() {
  for (auto *strategy : strategies_) {
    delete strategy;
  }
}

bool PosTagging::Init() {
  for (auto &strategy : strategies_) {
    if (!strategy->Init()) {
      FATAL("fail_init_strategy");
      return false;
    }
  }
  return true;
}

void PosTagging::Process(basic::NluContext &nluContext) {
  for (auto &strategy : strategies_) {
    strategy->Process(nluContext);
  }
}

bool PosTagging::Init(const xforce::JsonType &confPos) {
  bool ret = Conf::Get().Init(confPos);
  if (!ret) {
    FATAL("fail_init_conf[pos_tagging]");
    return false;
  }

  ret = posTagging_.Init();
  if (!ret) {
    FATAL("fail_init_pos_tagging");
    return false;
  }
  return true;
}

void PosTagging::Tagging(basic::NluContext &nluContext) {
  posTagging_.Process(nluContext);
}

void PosTagging::Tini() {}

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
