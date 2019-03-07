#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class Chunker {
 public: 
  bool Init(const xforce::JsonType &confJson);

  void Parse(
          IN const std::wstring &query,
          OUT basic::FragmentSet<basic::Segment> &segments,
          OUT basic::FragmentSet<ner::NameEntity> &nameEntities);

  void Tini();
};  

}}}
