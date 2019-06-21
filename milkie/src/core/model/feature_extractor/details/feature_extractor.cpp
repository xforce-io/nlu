#include "../feature_extractor.h"
#include "../parser/struct_feature_extractor.h"
#include "../instruction_feature_extractor.h"
#include "../../context/context.h"
#include "../../pattern_expr/pattern_expr.h"
#include "../../refer/refer_manager.h"

namespace xforce { namespace nlu { namespace milkie {

FeatureExtractor::FeatureExtractor(
    std::shared_ptr<StructFeatureExtractor> structFeatureExtractor,
    const std::string &filepath) {
  filepath_ = filepath;
  name_ = structFeatureExtractor->GetName();
  instructions_ = structFeatureExtractor->GetInstructions();
}

Errno::Code FeatureExtractor::MatchPattern(Context &context, size_t offset) const {
  bool ok = false;
  for (auto &instruction : instructions_) {
    context.Reset(offset);
    switch (instruction->GetCategoryInstruction()) {
      case CategoryInstruction::kPatternExpr : {
        if (
            (instruction->GetMatchType() == MatchType::kExactMatch &&
              instruction->GetPatternExpr()->ExactMatch(context)) ||
            (instruction->GetMatchType() == MatchType::kPrefixMatch &&
              instruction->GetPatternExpr()->MatchPattern(context, false)) ||
            (instruction->GetMatchType() == MatchType::kPartlyMatch &&
             instruction->GetPatternExpr()->PartlyMatch(context, false))) {
          ok = true;
        }
        break;
      }
      default : {
        FATAL("invalid_feature_extractor_instruction["
            << instruction->GetCategoryInstruction()
            << "]");
        return Errno::kOther;
      }
    }
  }
  return ok ? Errno::kOk : Errno::kNotMatched;
}

bool FeatureExtractor::Build(
      ReferManager &referManager,
      const std::string &filepath,
      std::vector<std::shared_ptr<FeatureExtractor>> &featureExtractors) {
  std::vector<std::shared_ptr<StructFeatureExtractor>> result;
  bool ret = StructFeatureExtractor::Parse(referManager, filepath, result);
  if (!ret) {
    FATAL("fail_parse_struct_feature_extractor_from[" << *StrHelper::Str2Wstr(filepath) << "]");
    return false;
  }

  for (auto &structFeatureExtractor : result) {
    featureExtractors.push_back(std::make_shared<FeatureExtractor>(structFeatureExtractor, filepath));
  }
  return true;
}

}}}

