#include "../feature_comb.h"

namespace xforce { namespace nlu { namespace pos {

std::hash<std::wstring> HashFeatureComb3::hashFunc;

int FeatureComb3::Load(const std::string &str) {
  std::vector<std::string> items;
  StrHelper::SplitStr(str, kSep, items);
  if (items.size() != 3) {
    FATAL("fail_load_feature_comb3[" << *StrHelper::Str2Wstr(str) << "]");
    return -1;
  }

  feature0 = *(StrHelper::Str2Wstr(items[0]));
  feature1 = *(StrHelper::Str2Wstr(items[1]));
  feature2 = *(StrHelper::Str2Wstr(items[2]));
  return 0;
}

void FeatureComb3::Dump(std::stringstream &ss) const {
  ss << *StrHelper::Wstr2Str(feature0) << kSep;
  ss << *StrHelper::Wstr2Str(feature1) << kSep;
  ss << *StrHelper::Wstr2Str(feature2);
}

}}}
