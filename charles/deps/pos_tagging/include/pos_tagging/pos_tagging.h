#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace pos {

class PosTagging {
 public: 
  static void Tagging(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments);
};

}}}
