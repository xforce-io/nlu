#include "../feature_comb.h"

namespace xforce { namespace nlu { namespace pos {

std::hash<std::wstring> HashFeatureComb3::hashFunc;

void FeatureComb3::Dump(std::stringstream &ss) const {
  ss << *StrHelper::Wstr2Str(feature0) << kSep;
  ss << *StrHelper::Wstr2Str(feature1) << kSep;
  ss << *StrHelper::Wstr2Str(feature2);
}

}}}
