#include "../statistics_unit.h"

namespace xforce { namespace nlu { namespace pos {

int StatisticsUnit::Load(const std::string &str) {
  std::vector<std::string> items;
  StrHelper::SplitStr(str, kSep, items);
  if (items.size() != 4) {
    FATAL("invalid_statistics_unit_load_str[" << *StrHelper::Str2Wstr(str) << "]");
    return -1;
  }

  size_t tmpType0, tmpType1, tmpType2;

  bool ret = StrHelper::GetNum(*StrHelper::Str2Wstr(items[0]), tmpType0);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_unit[" << *StrHelper::Str2Wstr(items[0]) << "]");
    return -2;
  }

  ret = StrHelper::GetNum(*StrHelper::Str2Wstr(items[1]), tmpType1);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_unit[" << *StrHelper::Str2Wstr(items[1]) << "]");
    return -3;
  }

  ret = StrHelper::GetNum(*StrHelper::Str2Wstr(items[2]), tmpType2);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_unit[" << *StrHelper::Str2Wstr(items[2]) << "]");
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
