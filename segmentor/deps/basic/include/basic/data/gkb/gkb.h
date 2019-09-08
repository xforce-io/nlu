#pragma once

#include "../../public.h"
#include "table/gkb_global.h"
#include "table/gkb_verb.h"
#include "table/gkb_adj.h"
#include "table/gkb_adv.h"
#include "table/gkb_prep.h"

namespace xforce { namespace nlu { namespace basic {

class Gkb {
 public:
  Gkb();
  virtual ~Gkb();

  bool Init(const std::string &dir);

  bool IsPhrase(const std::wstring &word0, const std::wstring &word1) const;

  const GkbGlobal& GetGkbGlobal() const { return *gkbGlobal_; }
  const GkbVerb& GetGkbVerb() const { return *gkbVerb_; }
  const GkbAdj& GetGkbAdj() const { return *gkbAdj_; }
  const GkbAdv& GetGkbAdv() const { return *gkbAdv_; }
  const GkbPrep& GetGkbPrep() const { return *gkbPrep_; }

 private:
  GkbGlobal *gkbGlobal_;
  GkbVerb *gkbVerb_;
  GkbAdj *gkbAdj_;
  GkbAdv *gkbAdv_;
  GkbPrep *gkbPrep_;
};

}}}
