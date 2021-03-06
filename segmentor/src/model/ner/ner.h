#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Ner {
 public: 
  enum Category {
    kCategoryNone = -1,
    kCategoryTime = 1,
    kCategoryNumber = 2,
    kCategoryPublication = 3,
    kCategoryName = 4,
    kCategoryOther = 100,
  };

 public: 
  virtual int GetCategory() const = 0; 
};

}}}
