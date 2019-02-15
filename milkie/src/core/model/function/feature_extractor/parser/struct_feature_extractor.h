#pragma once

#include "../../../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class InstructionFeatureExtractor;

class StructFeatureExtractor {
 public:
  static std::vector<std::shared_ptr<StructFeatureExtractor>> Parse(const std::wstring &filepath);

 private:
  void ProcessSingleLine_(
          const std::wstring &line,
          std::vector<std::shared_ptr<StructFeatureExtractor>> &structFeatureExtractors);

 private:
  std::wstring name_;
  std::vector<std::shared_ptr<InstructionFeatureExtractor>> instructions_;
};

}}}
