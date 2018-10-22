#include "../nature_bigram.h"
#include "../nature_dict.h"

namespace xforce { namespace nlu {

NatureBigram::NatureBigram() :
  count_(NULL) {}

bool NatureBigram::Init(const NatureDict &natureDict, const std::string &dictpath) {
  natureDict_ = &natureDict;

  count_ = new uint32_t* [natureDict.GetIndexSize()];
  for (uint32_t i=0; i < natureDict.GetIndexSize(); ++i) {
    count_[i] = new uint32_t [natureDict.GetIndexSize()];
  }

  FILE *fp = fopen(dictpath.c_str(), "r");
  if (fp == NULL) {
    ERROR("fail_open_filepath[" << dictpath << "]");
    return false;
  }

  char buf[4096];
  char *line = fgets(buf, sizeof(buf), fp);
  std::vector<std::string> results;
  uint32_t numLine = 0;
  while (NULL!=line) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (buf[strlen(buf) - 1] == '\r') {
      buf[strlen(buf) - 1] = '\0';
    }

    if (strlen(buf) > 0) {
      StrHelper::SplitStr(buf, '\t', results);
      if (results.size() != natureDict.GetIndexSize()) {
        ERROR("invalid_nature_dict_format[invalid_line_cnt]");
        return false;
      }

      for (uint32_t i=0; i < results.size(); ++i) {
        uint32_t num;
        bool ret = StrHelper::GetNum(results[i].c_str(), num);
        if (!ret) {
          ERROR("invalid_nature_bigram[" << buf << "]");
          return false;
        }
        count_[numLine][i] = ret;
      }
      ++numLine;
    }
    line = fgets(buf, sizeof(buf), fp);
  }

  if (numLine != natureDict.GetIndexSize()) {
      ERROR("invalid_nature_dict_format[invalid_num_line]");
      return false;
  } 
  return true;
}

NatureBigram::~NatureBigram() {
  for (uint32_t i=0; i < natureDict_->GetIndexSize(); ++i) {
    delete [] count_[i];
  }
}

}}
