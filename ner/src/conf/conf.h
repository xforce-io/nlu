#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf {
 public: 
  Conf();

  bool Init(const xforce::JsonType &confJson); 

  inline const std::string& GetDataDir() const;
 
  static Conf& Get() { return *conf_; }
  static void Tini();

 private: 
  std::string dataDir_;

  static Conf *conf_;
};

const std::string& Conf::GetDataDir() const {
  return dataDir_;
}

}}}
