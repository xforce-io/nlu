#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class StructPatternItemStr : public StructPatternItem {
 public: 
  inline StructPatternItemStr(
      const std::string &statement, 
      const std::vector<std::string> &args, 
      const std::string &patternStr);

  std::shared_ptr<PatternItem> BuildPattern();

  static std::shared_ptr<StructPatternItemStr> Build(const std::string &statement);

  const std::wstring& GetPatternStr() const { return patternStr_; }
 
 private:
  std::wstring patternStr_; 
};

StructPatternItemStr::StructPatternItemStr(
      const std::string &statement, 
      const std::vector<std::string> &args, 
      const std::string &patternStr) :
  StructPatternItem(),
  patternStr_(patternStr) {}
