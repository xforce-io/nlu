#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf {
 public: 
  Conf();

  bool Init(const std::string &filepath);
  bool Init(const xforce::JsonType &confJson);

  inline const std::vector<std::string>& GetExprFilepaths() const;
  inline const std::vector<std::string>& GetReferFilepaths() const;

 private:
  std::vector<std::string> exprFilepaths_;
  std::vector<std::string> referFilepaths_;
};

const std::vector<std::string>& Conf::GetExprFilepaths() const {
  return exprFilepaths_;
}

const std::vector<std::string>& Conf::GetReferFilepaths() const {
  return referFilepaths_;
}

}}}
