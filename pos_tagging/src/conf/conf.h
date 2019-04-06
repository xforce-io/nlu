#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace pos {

class Conf {
 public: 
  Conf();

  bool Init(const xforce::JsonType &filepath); 

  inline const std::string& GetDataDir() const;
  inline const std::string& GetLabeledDataPath() const;
 
  static Conf& Get() { return *conf_; }
  static void Tini();

 private: 
  std::string dataDir_;
  std::string labeledDataPath_;

  static Conf *conf_;
};

const std::string& Conf::GetDataDir() const {
  return dataDir_;
}

const std::string& Conf::GetLabeledDataPath() const {
  return labeledDataPath_;
}

}}}
