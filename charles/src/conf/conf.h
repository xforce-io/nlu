#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class Conf {
 public: 
  Conf();

  bool Init(const xforce::JsonType &confJson); 

  inline const std::string& GetDataDir() const;
  inline const std::string& GetSplitRuleConfpath() const;
 
  static Conf& Get() { return *conf_; }
  static void Tini();

 private: 
  std::string dataDir_;
  std::string splitRuleConfpath_;

  static Conf *conf_;
};

const std::string& Conf::GetDataDir() const {
  return dataDir_;
}

const std::string& Conf::GetSplitRuleConfpath() const {
  return splitRuleConfpath_;
}

}}}
