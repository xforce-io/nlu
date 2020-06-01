#pragma once

#include "../../../public.h"
#include "../entry/entry_conj.h"
#include "table.hpp"

namespace xforce { namespace nlu { namespace basic {

class GkbConj : public Table<EntryConj> {
 private:
  typedef Table<EntryConj> Super;

 public:
  virtual bool Init(
          const std::string &dir,
          const std::string &filepath);

  bool Pos(
          const std::wstring &word,
          bool &prev,
          bool &mid,
          bool &post) const;
};

}}}
