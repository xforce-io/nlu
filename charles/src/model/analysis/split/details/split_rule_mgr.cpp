#include "../split_rule_mgr.h"
#include "../rule_pos_tag.h"
#include "../rule_syntax_rule.h"
#include "../rule_syntax_prep.h"
#include "../../../../conf/conf.h"

namespace xforce { namespace nlu { namespace charles {

SplitRuleMgr::SplitRuleMgr() :
    splitRuleEngine_(nullptr) {
  allRules_.resize(basic::Stage::kEnd);
  for (size_t i=0; i < allRules_.size(); ++i) {
    allRules_[i] = nullptr;
  }
  allRules_[basic::Stage::kPosTag] = new Rules();
  allRules_[basic::Stage::kSyntax] = new Rules();
}

SplitRuleMgr::~SplitRuleMgr() {
  XFC_DELETE(splitRuleEngine_)
  for (auto *rules : allRules_) {
    if (nullptr != rules) {
      for (auto *rule : *rules) {
        delete rule;
      }
    }
    delete rules;
  }
}

bool SplitRuleMgr::Init(const basic::NluContext &nluContext) {
  allRules_[basic::Stage::kPosTag]->push_back(new RulePosTagMultiTag());
  return InitSyntax_(nluContext);
}

bool SplitRuleMgr::InitSyntax_(const basic::NluContext &nluContext) {
  return InitSyntaxForPrep_(nluContext) ||
      InitSyntaxFromRules_(nluContext);
}

bool SplitRuleMgr::InitSyntaxFromRules_(const basic::NluContext &nluContext) {
  splitRuleEngine_ = new milkie::Milkie();

  bool ret = splitRuleEngine_->Init(Conf::Get().GetSplitRuleConfpath());
  if (!ret) {
    FATAL("fail_init[split_rule_engine] confpath["
                  << *StrHelper::Str2Wstr(Conf::Get().GetSplitRuleConfpath())
                  << "]");
    return false;
  }

  auto featureExtractors = splitRuleEngine_->GetManager().GetFeatureExtractors();
  for (auto kv : featureExtractors) {
    allRules_[basic::Stage::kSyntax]->push_back(new RuleSyntaxRule(kv.second));
  }
  return true;
}

bool SplitRuleMgr::InitSyntaxForPrep_(const basic::NluContext &nluContext) {
  size_t idx=0;
  for (auto segment : nluContext.GetSegments().GetAll()) {
    if (segment->GetTag() == basic::PosTag::Type::kP) {
      allRules_[basic::Stage::kSyntax]->push_back(new RuleSyntaxPrep(idx));
    }
    ++idx;
  }
  return true;
}

}}}
