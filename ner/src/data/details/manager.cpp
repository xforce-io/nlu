#include "../manager.h"
#include "../surname.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace ner {

Manager *Manager::manager_ = new Manager();

bool Manager::Init() {
  std::stringstream ss;
  std::vector<std::string> wordDictPaths;

  ss << Conf::Get().GetDataDir() << "data/surname.dic";
  surname_ = new Surname();    
  bool ret = surname_->Init(ss.str());
  XFC_FAIL_HANDLE_WARN(!ret, "fail_init_surname")

  return true;

  ERROR_HANDLE:
  return false;
}

Manager::~Manager() {
  XFC_DELETE(surname_)
}

void Manager::Tini() {
  XFC_DELETE(manager_)
}

}}}
