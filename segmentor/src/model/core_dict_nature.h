#pragma once

#include "public.h"
#include "../data/manager.h"
#include "../data/nature_dict.h"

namespace xforce { namespace nlu { namespace segmentor {

class CoreDictNature {
 public:
  inline bool Init(const std::string &name, size_t freq);

  const std::string &GetName() const { return name_; }
  size_t GetFreq() const { return freq_; }
  const Nature& GetNature() const { return *nature_; }

 private:
  std::string name_;
  size_t freq_;
  const Nature *nature_;
};

bool CoreDictNature::Init(const std::string &name, size_t freq) {
  name_ = name;
  freq_ = freq;
  nature_ = Manager::Get().GetNatureDict().GetNature(name);
  return true;
}

}}}
