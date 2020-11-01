#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf;
class StructFeatureExtractor;  
class Context;
class ReferManager;
class InstructionFeatureExtractor;

class FeatureExtractor {
 public:
  FeatureExtractor(
          std::shared_ptr<StructFeatureExtractor> structFeatureExtractor,
          const std::string &filepath);

  const std::string& GetFilepath() const { return filepath_; }
  const std::wstring& GetName() const { return name_; }
  Errno::Code MatchPattern(Context &context, size_t offset=0) const;

 public: 
  static bool Build(
          const Conf &conf,
          ReferManager &referManager,
          const std::string &filepath,
          std::vector<std::shared_ptr<FeatureExtractor>> &featureExtractors);

 private:
  std::string filepath_;
  std::wstring name_;
  std::vector<std::shared_ptr<InstructionFeatureExtractor>> instructions_;
};

}}}
