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
      OUT basic::FragmentSet<basic::Segment> &segments,
      OUT basic::FragmentSet<basic::NameEntity> &nameEntities);

  static void Tini();
};

}}}
