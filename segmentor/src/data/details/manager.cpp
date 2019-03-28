#include "../manager.h"
#include "../word_dict.h"
#include "../bigram_dict.h"
#include "../nature_bigram.h"
#include "../nature_dict.h"
#include "../surname.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace segmentor {

Manager *Manager::manager_ = new Manager();

bool Manager::Init() {
  std::stringstream ss;
  std::vector<std::string> wordDictPaths;

  ss << Conf::Get().GetDataDir() << "data/bigramdict.dic";
  bigramDict_ = new BigramDict();
  bool ret = bigramDict_->Init(ss.str());
  XFC_FAIL_HANDLE_FATAL(!ret, "fail_init_bigram_dict")

  ss.str("");  
  ss << Conf::Get().GetDataDir() << "data/nature/nature.map";
  natureDict_ = new NatureDict();  
  ret = natureDict_->Init(ss.str());
  XFC_FAIL_HANDLE_FATAL(!ret, "fail_init_nature_dict")

  ss.str("");  
  ss << Conf::Get().GetDataDir() << "data/nature/nature.table";
  natureBigram_ = new NatureBigram();  
  ret = natureBigram_->Init(*natureDict_, ss.str());
  XFC_FAIL_HANDLE_FATAL(!ret, "fail_init_nature_bigram")

  ss.str("");  
  ss << Conf::Get().GetDataDir() << "data/word/core.dic";
  wordDictPaths.push_back(ss.str());
  ss.str("");
  ss << Conf::Get().GetDataDir() << "data/word/china_province_city_county.dic";
  wordDictPaths.push_back(ss.str());
  wordDict_ = new WordDict();
  ret = wordDict_->Init(wordDictPaths);
  XFC_FAIL_HANDLE_FATAL(!ret, "fail_init_word_dict")

  return true;

  ERROR_HANDLE:
  return false;
}  

Manager::~Manager() {
  XFC_DELETE(wordDict_)
  XFC_DELETE(natureBigram_)
  XFC_DELETE(natureDict_)
  XFC_DELETE(bigramDict_)
}

void Manager::Tini() {
  XFC_DELETE(manager_)
}

}}}
