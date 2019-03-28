#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

struct Nature {
 public:
  Nature(const std::string &name, uint32_t index, uint32_t freq); 

 public: 
  std::string name; 
  uint32_t index;
  uint32_t freq;
};  

Nature::Nature(const std::string &nameArg, uint32_t indexArg, uint32_t freqArg) :
    name(nameArg),
    index(indexArg),
    freq(freqArg) {}

}}}
