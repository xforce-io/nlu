#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Segmentor {
 public: 
  static bool Init(const std::string &confpath);

  static void Parse(
      IN const std::wstring &query, 
      OUT std::vector<size_t> &offsets,
      OUT std::vector<ner::NameEntity*> &nameEntities);

  static void Tini();
};

}}}
