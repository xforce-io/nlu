#include "../statistics_unit.h"

namespace xforce { namespace nlu { namespace pos {

void StatisticsUnit::CalcConfidence(size_t totalCnt) {
  if (count == totalCnt && count>10) {
    confidence.SetScore(100+count-10);
  } else {
    confidence.SetScore(count*100/totalCnt + count/50);
  }
}

int StatisticsUnit::Load(const std::string &str) {
  std::vector<std::string> items;
  StrHelper::SplitStr(str, kSep, items);
  if (items.size() != 4) {
    FATAL("invalid_statistics_unit_load_str[" << *StrHelper::Str2Wstr(str) << "]");
    return -1;
  }

  size_t tmpType0, tmpType1, tmpType2;

  bool ret = StrHelper::GetNum(items[0], tmpType0);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_str0[" << *StrHelper::Str2Wstr(str) << "]");
    return -2;
  }

  ret = StrHelper::GetNum(items[1], tmpType1);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_str1[" << *StrHelper::Str2Wstr(str) << "]");
    return -3;
  }

  ret = StrHelper::GetNum(items[2], tmpType2);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_str2[" << *StrHelper::Str2Wstr(str) << "]");
    return -4;
  }

  type0 = static_cast<basic::PosTag::Type::Val>(tmpType0);
  type1 = static_cast<basic::PosTag::Type::Val>(tmpType1);
  type2 = static_cast<basic::PosTag::Type::Val>(tmpType2);

  ret = StrHelper::GetNum(items[3], count);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_str_invalid_count[" 
        << *StrHelper::Str2Wstr(items[3]) 
        << "]");
    return -5;
  }
  return 0;
}

void StatisticsUnit::Dump(std::stringstream &ss) const {
  ss << type0 << kSep;
  ss << type1 << kSep;
  ss << type2 << kSep;
  ss << count;
}

}}}
