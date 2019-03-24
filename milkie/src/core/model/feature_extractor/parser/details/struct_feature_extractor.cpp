#include "../struct_feature_extractor.h"
#include "../../../refer/refer_manager.h"
#include "../../../pattern_expr/pattern_expr.h"
#include "../../instruction_feature_extractor.h"

namespace xforce { namespace nlu { namespace milkie {

const std::wstring StructFeatureExtractor::kKeywordBegin = L"FEATURE_EXTRACTOR_BEGIN";
const std::wstring StructFeatureExtractor::kKeywordEnd = L"FEATURE_EXTRACTOR_END";

StructFeatureExtractor::StructFeatureExtractor(
    const std::wstring &name,
    const std::vector<std::shared_ptr<InstructionFeatureExtractor>> &instructions) {
  name_ = name;
  instructions_ = instructions;
}

bool StructFeatureExtractor::Parse(
        ReferManager &referManager,
        const std::string &filepath,
        std::vector<std::shared_ptr<StructFeatureExtractor>> &results) {
  std::vector<std::string> lines;
  bool ret = IOHelper::ReadLinesFromFilepath(filepath, lines);
  if (!ret) {
    FATAL("fail_readline_from[" << *(StrHelper::Str2Wstr(filepath)) << "]");
    return false;
  }

  std::wstring curName;
  std::vector<std::shared_ptr<InstructionFeatureExtractor>> curInstructions;

  bool insideFunction = false;
  for (auto &line : lines) {
    auto lineAfterProcess = Helper::PreprocessExprLine(*StrHelper::Str2Wstr(line));
    if (lineAfterProcess.substr(0, kKeywordBegin.length()) == kKeywordBegin) {
      insideFunction = true;

      curInstructions.clear();
      auto idxNameBegin = lineAfterProcess.find(L'(');
      auto idxNameEnd = lineAfterProcess.find(L')');
      if (std::wstring::npos == idxNameBegin || std::wstring::npos == idxNameEnd || idxNameBegin>idxNameEnd) {
        FATAL("invalid_feature_extractor_declaration[" << lineAfterProcess << "]");
        return false;
      }

      curName = lineAfterProcess.substr(idxNameBegin+1, idxNameEnd-idxNameBegin-1);
    } else if (!insideFunction ||
        lineAfterProcess.empty() ||
        lineAfterProcess.substr(0, 2) == L"//") {
      continue;
    } else if (lineAfterProcess.substr(0, kKeywordEnd.length()) == kKeywordEnd) {
      results.push_back(std::make_shared<StructFeatureExtractor>(curName, curInstructions));
      insideFunction = false;
    } else if (PatternExpr::IsPatternExprStartingChar(lineAfterProcess.at(0))) {
      MatchType::Type matchType = MatchType::kOtherMatch;
      if (PatternExpr::IsPatternExprPrefixStartingChar(lineAfterProcess.at(0))) {
        matchType = MatchType::kPrefixMatch;
      } else if (PatternExpr::IsPatternExprPartlyStartingChar(lineAfterProcess.at(0))) {
        matchType = MatchType::kPartlyMatch;
      } else {
        matchType = MatchType::kExactMatch;
      }

      std::shared_ptr<PatternExpr> patternExpr;
      if (MatchType::kExactMatch == matchType) {
        patternExpr = PatternExpr::Build(curName, lineAfterProcess).first;
      } else {
        patternExpr = PatternExpr::Build(curName, lineAfterProcess.substr(1)).first;
      }

      if (patternExpr->GetRepeatPattern() != CategoryPatternExpr::kOnce) {
        FATAL("feature_extractor_category_pattern_expr_should_be_once");
        return false;
      }

      curInstructions.push_back(
              std::make_shared<InstructionFeatureExtractor>(
                      patternExpr, matchType));
    } else if (lineAfterProcess.find(L'=') != std::wstring::npos) {
      ret = referManager.PutLocalRefer(curName, lineAfterProcess);
      if (!ret) {
        FATAL("fail_put_into_refer[" << curName << "]");
        return false;
      }
    } else {
      FATAL("invalid_feature_extractor_line[" << *StrHelper::Str2Wstr(line) << "]");
      return false;
    }
  }
  return true;
}


}}}
