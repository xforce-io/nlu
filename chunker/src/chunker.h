#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace chunker {

class Matcher;

class Chunker {
 public: 
  Chunker(); 

  bool Init(const xforce::JsonType &confJson);

  void Parse(
          IN const std::wstring &query,
          IN const basic::FragmentSet<basic::Segment> &segments,
          IN const basic::FragmentSet<basic::NameEntity> &nameEntities,
          OUT basic::FragmentSet<basic::Chunk> &chunks);

  void Tini();

 private:
  Matcher *matcher_;
};

}}}
