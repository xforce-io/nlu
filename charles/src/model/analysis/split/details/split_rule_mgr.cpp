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
  allRules_[basic::Stage::kSegment] = new Rules();
  allRules_[basic::Stage::kPosTag] = new Rules();
  allRules_[basic::Stage::kChunk] = new Rules();
  allRules_[basic::Stage::kSyntax] = new Rules();
}

SplitRuleMgr::~SplitRuleMgr() {
  Clear();
  for (auto *rules : allRules_) {
    delete rules;
  }
}

bool SplitRuleMgr::Init(const basic::NluContext &nluContext) {
  return InitForOffset_(nluContext) && InitSyntaxFromRules_(nluContext);
}

void SplitRuleMgr::Adjust(const basic::NluContext &nluContext) {
  Clear();
  Init(nluContext);
}

SplitRuleMgr* SplitRuleMgr::Clone() const {
  auto result = new SplitRuleMgr();
  for (size_t i=0; i < allRules_.size(); ++i) {
    Rules *rules = allRules_[i];
    if (nullptr!=rules) {
      Rules *newRules = new Rules();
      for (auto *rule : *rules) {
        newRules->push_back(rule->Clone());
      }
      result->allRules_.push_back(newRules);
    } else {
      result->allRules_.push_back(nullptr);
    }
  }
  result->splitRuleEngine_ = splitRuleEngine_;
  return result;
}

void SplitRuleMgr::Clear() {
  for (auto *rules : allRules_) {
    if (nullptr != rules) {
      for (auto *rule : *rules) {
        if (nullptr != rule) {
          delete rule;
        }
      }
      rules->clear();
    }
  }
}

bool SplitRuleMgr::InitForOffset_(const basic::NluContext &nluContext) {
  size_t idx=0;
  for (auto segment : nluContext.GetSegments().GetAll()) {
    if (segment->GetTag() == basic::PosTag::Type::kP) {
      allRules_[basic::Stage::kSyntax]->push_back(new RuleSyntaxPrep(segment->GetOffset()));
    } else if (segment->GetTags().size() > 1) {
      allRules_[basic::Stage::kPosTag]->push_back(new RulePosTagMultiTag(segment->GetOffset()));
    }
    ++idx;
  }
  return true;
}

bool SplitRuleMgr::InitSyntaxFromRules_(const basic::NluContext &nluContext) {
  splitRuleEngine_ = std::make_shared<milkie::Milkie>();

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

}}}
