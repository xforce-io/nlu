#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Conf {
 public: 
  Conf();

  bool Init(const std::string &filepath); 

  inline const std::string& GetDataDir() const;
 
  static Conf& Get() { return *conf_; }

 private: 
  std::string dataDir_;

  static Conf *conf_;
};

const std::string& Conf::GetDataDir() const {
  return dataDir_;
}

}}}
