#pragma once

#include "../../public.h"
#include "parser/struct_feature_extractor.h"

namespace xforce { namespace nlu { namespace milkie {

class Context;

class FeatureExtractor {
 public:
  FeatureExtractor(
          std::shared_ptr<StructFeatureExtractor> structFeatureExtractor,
          const std::string &filepath);

  const std::string& GetFilepath() const { return filepath_; }
  const std::wstring& GetName() const { return name_; }
  Errno::Code MatchPattern(Context &context);

 public: 
  static bool Build(
          const std::string &filepath,
          std::vector<std::shared_ptr<FeatureExtractor>> &featureExtractors);

 private:
  std::string filepath_;
  std::wstring name_;
  std::vector<std::shared_ptr<InstructionFeatureExtractor>> instructions_;
};

}}}
