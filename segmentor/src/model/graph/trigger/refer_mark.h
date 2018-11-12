#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class Ner::Category;  

struct ReferMark {
  char begin;
  char end;
  Ner::Category nerCategory;
};  

}}}
