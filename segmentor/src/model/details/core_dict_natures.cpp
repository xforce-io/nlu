#include "../core_dict_natures.h"
#include "../core_dict_nature.h"

namespace xforce { namespace nlu { namespace segmentor {

CoreDictNatures::CoreDictNatures() :
  mainNature_(nullptr),
  allFreq_(0) {}

bool CoreDictNatures::Init(const std::string &expr) {
  if (expr.size() <= 2) {
    ERROR("invalid_core_dict_natures[" << *StrHelper::Str2Wstr(expr) << "]");
    return false;
  }

  std::vector<std::string> items;
  StrHelper::SplitStr(expr.substr(1, expr.length() - 2), ',', items);
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    std::vector<std::string> kv;
    StrHelper::SplitStr(*iter, '=', kv);
    if (kv.size() != 2) {
      ERROR("invalid_core_dict_natures_format[" << *StrHelper::Str2Wstr(*iter) << "]");
      return false;
    }

    std::string key = StrHelper::Trim(kv[0]);
    size_t val;
    bool ret = StrHelper::GetNum(kv[1].c_str(), val);
    if (!ret) {
      ERROR("invalid_core_dict_natures_format[" << *StrHelper::Str2Wstr(*iter) << "]");
      return false;
    }
      
    CoreDictNature *coreDictNature = new CoreDictNature();
    ret = coreDictNature->Init(key, val);
    if (!ret) {
      ERROR("fail_init_core_dict_nature[" << *(StrHelper::Str2Wstr(key)) << "|" << val << "]");
      return false;
    }
    coreDictNatures_.push_back(coreDictNature);
  }
  Init_();
  return true;
}

bool CoreDictNatures::Init(const CoreDictNature &coreDictNature) {
  coreDictNatures_.push_back(&coreDictNature);
  Init_();
  return true;
}

bool CoreDictNatures::Init(const std::vector<const CoreDictNature*> &coreDictNatures) {
  coreDictNatures_ = coreDictNatures;
  Init_();
  return true;
}

CoreDictNatures::~CoreDictNatures() {
  for (auto iter = coreDictNatures_.begin(); iter != coreDictNatures_.end(); ++iter) {
    XFC_DELETE(*iter)
  }
}

void CoreDictNatures::Init_() {
  ssize_t maxFreq = -1;
  const CoreDictNature *tmpNature = nullptr;
  for (auto iter = coreDictNatures_.begin(); iter != coreDictNatures_.end(); ++iter) {
    const CoreDictNature *coreDictNature = *iter;
    if (maxFreq < ssize_t(coreDictNature->GetFreq())) {
      maxFreq = coreDictNature->GetFreq();
      tmpNature = coreDictNature;
    }
    allFreq_ += coreDictNature->GetFreq();
  }

  if (0 == allFreq_) {
    allFreq_ = 1;
  }

  if (nullptr != tmpNature) {
    mainNature_ = tmpNature;
  }
}

}}}
