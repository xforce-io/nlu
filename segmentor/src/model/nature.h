#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

struct Nature {
 public:
  inline Nature(const std::string &name, uint32_t index, uint32_t freq);

  inline basic::PosTag::Type::Val GetPosTag() const;

 public: 
  std::string name; 
  uint32_t index;
  uint32_t freq;
};  

Nature::Nature(const std::string &nameArg, uint32_t indexArg, uint32_t freqArg) :
    name(nameArg),
    index(indexArg),
    freq(freqArg) {}

basic::PosTag::Type::Val Nature::GetPosTag() const {
  if (name.length() >= 1) {
    if (name[0] == 'n') {
      return basic::PosTag::Type::kN;
    } else if (name[0] == 'v') {
      if (name.length() >= 2 && name[1] == 'n') {
        return basic::PosTag::Type::kVn;
      } else {
        return basic::PosTag::Type::kV;
      }
    }
  }
  return basic::PosTag::Type::kUndef;
}

}}}
