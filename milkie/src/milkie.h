#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Conf;
class ReferManager;
class Manager;

class Milkie {
 public:
  Milkie();
  bool Init(const std::string &confpath);
  virtual ~Milkie();

 private:
  Conf *conf_;
  ReferManager *referManager_;
  Manager *manager_;
};

}}}
