#pragma once

namespace xforce { namespace nlu { namespace basic {

class Chunk {
 public:
  enum Tag {
      kNP,
      kVP,
      kADVP,
      kPP,
      kUndef
  };
};

}}}
