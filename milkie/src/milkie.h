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

  const Conf& GetConf() const { return *conf_; }
  const ReferManager& GetReferManager() const { return *referManager_; }
  const Manager& GetManager() const { return *manager_; }

  virtual ~Milkie();

 private:
  Conf *conf_;
  ReferManager *referManager_;
  Manager *manager_;
};

}}}
