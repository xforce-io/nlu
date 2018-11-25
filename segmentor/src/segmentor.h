#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Segmentor {
 public: 
  static bool Init(
    const xforce::JsonType &confSeg,
    const xforce::JsonType &confNer);

  static void Parse(
      IN const std::wstring &query, 
      OUT std::vector<size_t> &offsets,
      OUT std::vector<std::shared_ptr<ner::NameEntity>> &nameEntities);

  static void Tini();
};

}}}
