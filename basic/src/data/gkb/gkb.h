#pragma once

#include "../../public.h"
#include "table/gkb_adv.h"

namespace xforce { namespace nlu { namespace basic {

class Gkb {
 public:
  Gkb();
  virtual ~Gkb();

  bool Init(const std::string &dir);

  const GkbAdv& GetGkbAdv() const { return *gkbAdv_; }

 private:
  GkbAdv *gkbAdv_;
};

}}}
