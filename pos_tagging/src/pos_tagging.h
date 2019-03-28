#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace pos {

class PosTagging {
 public: 
  static void Tagging(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments);

 private:
  static void SetPosForWordWithUniqPos_(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments);

  static void SetPosCtbFromPos_(
      const std::wstring &clause,
      basic::FragmentSet<basic::Segment> &segments);
};

}}}
