#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class CoreDictNature;  

class CoreDictNatures {
 public: 
  CoreDictNatures();

  bool Init(const std::string &expr); 
  bool Init(const CoreDictNature &coreDictNature);
  bool Init(const std::vector<const CoreDictNature*> &coreDictNatures);

  const CoreDictNature* GetMainNature() const { return mainNature_; }
  size_t GetFreq() const { return allFreq_; }

  virtual ~CoreDictNatures();
 
 private:
  //init given coreDictNatures_
  void Init_();
 
 private:
  std::vector<const CoreDictNature*> coreDictNatures_; 
  const CoreDictNature *mainNature_;
  size_t allFreq_;
};

}}}
