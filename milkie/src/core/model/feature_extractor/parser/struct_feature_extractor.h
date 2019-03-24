#pragma once

#include "../../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class ReferManager;
class InstructionFeatureExtractor;

class StructFeatureExtractor {
 private:
  static const std::wstring kKeywordBegin;
  static const std::wstring kKeywordEnd;

 public:
  StructFeatureExtractor(
          const std::wstring &name,
          const std::vector<std::shared_ptr<InstructionFeatureExtractor>> &instructions);

  const std::wstring& GetName() const { return name_; }
  const std::vector<std::shared_ptr<InstructionFeatureExtractor>>& GetInstructions() const { return instructions_; }

 public:
  static bool Parse(
          ReferManager &referManager,
          const std::string &filepath,
          std::vector<std::shared_ptr<StructFeatureExtractor>> &results);

 private:
  std::wstring name_;
  std::vector<std::shared_ptr<InstructionFeatureExtractor>> instructions_;
};

}}}
