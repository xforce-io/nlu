#pragma once

#include "../../public.h"
#include "table/gkb_global.h"
#include "table/gkb_adv.h"

namespace xforce { namespace nlu { namespace basic {

class Gkb {
 public:
  Gkb();
  virtual ~Gkb();

  bool Init(const std::string &dir);

  const GkbGlobal& GetGkbGlobal() const { return *gkbGlobal_; }
  const GkbAdv& GetGkbAdv() const { return *gkbAdv_; }

 private:
  GkbGlobal *gkbGlobal_;
  GkbAdv *gkbAdv_;
};

}}}
