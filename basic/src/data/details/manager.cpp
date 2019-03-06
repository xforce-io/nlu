#include "../manager.h"
#include "../../conf/conf.h"
#include "../../data/word_dict.h"
#include "../../data/gkb_zk.h"

namespace xforce { namespace nlu { namespace basic {

Manager *Manager::manager_ = new Manager();

bool Manager::Init() {
  std::stringstream ss;

  ss << Conf::Get().GetDataDir() << "data/word.dict";
  wordDict_ = new WordDict();
  bool ret = wordDict_->Init(ss.str());
  XFC_FAIL_HANDLE_FATAL(!ret, "fail_init_word_dict")

  ss << Conf::Get().GetDataDir() << "data/gkb_zk";
  gkbZk_ = new GkbZk();
  ret = gkbZk_->Init(ss.str());
  XFC_FAIL_HANDLE_FATAL(!ret, "fail_init_gkb_zk")

  return true;

  ERROR_HANDLE:
  return false;
}

Manager::~Manager() {
  XFC_DELETE(wordDict_)
}

void Manager::Tini() {
  XFC_DELETE(manager_)
}

}}}
