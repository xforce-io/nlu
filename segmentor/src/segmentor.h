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
      OUT std::shared_ptr<basic::NluContext> &nluContext);

  static void Tini();
};

}}}
