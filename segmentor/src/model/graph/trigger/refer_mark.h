#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class Ner::Category;  

struct ReferMark {
  char begin;
  char end;
  Ner::Category nerCategory;
};  

}}
