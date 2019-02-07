#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf {
 public: 
  Conf();

  bool Init(const xforce::JsonType &filepath); 

  inline bool GetDebugMode() const;

  static Conf& Get() { return *conf_; }
  static void Tini();

 private: 
  bool debugMode_;

  static Conf *conf_;
};

bool Conf::GetDebugMode() const {
  return debugMode_;
}

}}}
