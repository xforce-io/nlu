#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class NatureDict;  

class NatureBigram {
 public:
  NatureBigram(); 

  bool Init(const NatureDict &natureDict, const std::string &dictpath);

  virtual ~NatureBigram();

 private:  
  const NatureDict *natureDict_;

  uint32_t **count_; 
};

}}
