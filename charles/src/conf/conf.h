#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class Conf {
 public: 
  Conf();

  bool Init(const xforce::JsonType &confJson); 

  const std::string& GetDataDir() const { return dataDir_; }
  const std::string& GetSplitRuleConfpath() const { return splitRuleConfpath_; }
  const std::string &GetHost() const { return host_; }
  int GetPort() const { return port_; }
 
  static Conf& Get() { return *conf_; }
  static void Tini();

 private: 
  std::string dataDir_;
  std::string splitRuleConfpath_;
  std::string host_;
  int port_;

  static Conf *conf_;
};

}}}
