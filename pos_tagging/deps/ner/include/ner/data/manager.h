#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace ner {

class Surname;  

class Manager {
 public: 
  bool Init(); 

  const Surname& GetSurname() const { return *surname_; }

  inline static void SetSurname(Surname &surname);

  virtual ~Manager();

  static Manager& Get() { return *manager_; }
  static void Tini();

 private:
  Surname *surname_;

  static Manager *manager_;
};

void Manager::SetSurname(Surname &surname) {
  manager_->surname_ = &surname;
}

}}}
