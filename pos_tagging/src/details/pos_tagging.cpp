#include "../pos_tagging.h"
#include "../conf/conf.h"
#include "../model/strategy_uniq.h"
#include "../model/strategy_window_statistics.h"
#include "../model/strategy_context_infer.h"
#include "../model/strategy_complement.h"
#include "../model/strategy_pos_deduction.h"
#include "../model/strategy_only_pred_or_prep.h"

namespace xforce { namespace nlu { namespace pos {

PosTagging PosTagging::posTagging_;

PosTagging::PosTagging() {
  strategies_.push_back(new StrategyUniq());
  strategies_.push_back(new StrategyWindowStatistics());
  strategies_.push_back(new StrategyComplement());
  strategies_.push_back(new StrategyPosDeduction());
  strategies_.push_back(new StrategyOnlyPredOrPrep());
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
  std::cout << "succ init pos" << std::endl;
  return true;
}

void PosTagging::Tagging(std::shared_ptr<basic::NluContext> nluContext) {
  posTagging_.Process(*nluContext);
}

void PosTagging::Tini() {}

}}}
