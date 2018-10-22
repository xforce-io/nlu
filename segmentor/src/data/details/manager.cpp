#include "../manager.h"
#include "../bigram_dict.h"
#include "../nature_bigram.h"
#include "../nature_dict.h"
#include "../surname.h"

namespace xforce { namespace nlu {

Manager *Manager::manager_ = new Manager();

bool Manager::Init() {
  bigramDict_ = new BigramDict();
  bool ret = bigramDict_->Init("data/bigramdict.dic");
  XFC_FAIL_HANDLE_WARN(!ret, "fail_init_bigram_dict")

  ret = natureDict_->Init("data/nature/nature.map");
  XFC_FAIL_HANDLE_WARN(!ret, "fail_init_nature_dict")

  ret = natureBigram_->Init(*natureDict_, "data/nature/nature.table");
  XFC_FAIL_HANDLE_WARN(!ret, "fail_init_nature_bigram")

  ret = surname_->Init("data/surname.dic");
  XFC_FAIL_HANDLE_WARN(!ret, "fail_init_surname")

  return true;

  ERROR_HANDLE:
  return false;
}  

}}
