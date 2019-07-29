#include "../split_stages.h"
#include "../rule_pos_tag.h"
#include "../../../../conf/conf.h"

namespace xforce { namespace nlu { namespace charles {

SplitStages::~SplitStages() {
  for (auto *rule : posTag_) {
    delete rule;
  }

  for (auto *rule : syntax_) {
    delete rule;
  }
}

bool SplitStages::Init() {
  posTag_.push_back(new RulePosTagMultiTag());
  return true;
}

bool SplitStages::InitSyntax_() {
  splitRuleEngine_ = new milkie::Milkie();

  bool ret = splitRuleEngine_->Init(Conf::Get().GetSplitRuleConfpath());
  if (!ret) {
    FATAL("fail_init[split_rule_engine] confpath["
                  << *StrHelper::Str2Wstr(Conf::Get().GetSplitRuleConfpath())
                  << "]");
    return false;
  }

  auto featureExtractors = splitRuleEngine_->GetManager().GetFeatureExtractors();
  return true;
}

}}}
