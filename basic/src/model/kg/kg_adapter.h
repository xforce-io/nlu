#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace basic {

class Entity;

class KgAdapter {
 public:
  virtual size_t DistCommonFather(
          const Entity &entity0,
          const Entity &entity1) = 0;
};

}}}