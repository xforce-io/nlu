#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf {
 public: 
  Conf();

  bool Init(const std::string &filepath);
  bool Init(const xforce::JsonType &confJson);

  inline bool GetDebugMode() const;
  inline const std::vector<std::string>& GetReferFilepaths() const;

  static Conf& Get() { return *conf_; }
  static void Tini();

 private: 
  bool debugMode_;
  std::vector<std::string> referFilepaths_;

  static Conf *conf_;
};

bool Conf::GetDebugMode() const {
  return debugMode_;
}

const std::vector<std::string>& Conf::GetReferFilepaths() const {
  return referFilepaths_;
}

}}}
