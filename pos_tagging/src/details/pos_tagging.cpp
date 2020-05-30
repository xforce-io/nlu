#include "../pos_tagging.h"
#include "../conf/conf.h"
#include "../model/strategy_uniq.h"
#include "../model/strategy_window_statistics.h"
#include "../model/strategy_context_infer.h"
#include "../model/strategy_complement.h"
#include "../model/strategy_pos_deduction.h"
#include "../model/strategy_only_pred_or_prep.h"
#include "../model/strategy_special_token.h"
#include "../model/strategy_len1.h"

namespace xforce { namespace nlu { namespace pos {

PosTagging PosTagging::posTagging_;

PosTagging::PosTagging() {
  strategies_.push_back(new StrategyUniq());
  strategies_.push_back(new StrategyWindowStatistics());
  strategies_.push_back(new StrategyComplement());
  strategies_.push_back(new StrategyPosDeduction());
  //strategies_.push_back(new StrategyOnlyPredOrPrep()); // 如果句子就是名词短语
  strategies_.push_back(new StrategySpecialToken());
  strategies_.push_back(new StrategyLen1());
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
  PostProcess_(nluContext);
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
  std::cout << "succ init pos" << std::endl;
  return true;
}

void PosTagging::Tagging(std::shared_ptr<basic::NluContext> nluContext) {
  posTagging_.Process(*nluContext);
}

void PosTagging::Tini() {}

void PosTagging::PostProcess_(basic::NluContext &nluContext) {
  while (true) {
    bool touched = false;

    auto &segs = nluContext.Get<basic::Segment>().GetAll();
    auto cur = segs.begin();
    if (cur == segs.end()) {
      return;
    }

    while (true) {
      auto next = cur;
      ++next;
      if (next == segs.end()) {
        return;
      }

      if ((*cur)->GetTag() == basic::PosTag::Type::kV &&
          (*next)->GetTag() == basic::PosTag::Type::kV) {
        bool ret = basic::Manager::Get().GetGkb().IsPhrase(
                (*cur)->GetStrFromSentence(nluContext.GetQuery()),
                (*next)->GetStrFromSentence(nluContext.GetQuery()));
        if (ret) {
          basic::Segment newSegment(
                  basic::PosTag::Type::kV,
                  (*cur)->GetOffset(),
                  (*cur)->GetLen() + (*next)->GetLen());
          auto afterNext = next;
          ++afterNext;
          nluContext.Get<basic::Segment>().Erase(cur, afterNext);
          nluContext.Add(newSegment);
          touched = true;
          break;
        }
      }
      cur = next;
    }

    if (!touched) {
      return;
    }
  }
}

}}}
