#include "../statistics_unit.h"

namespace xforce { namespace nlu { namespace pos {

int StatisticsUnit::Load(const std::string &str) {
  std::vector<std::string> items;
  StrHelper::SplitStr(str, kSep, items);
  if (items.size() != 4) {
    FATAL("invalid_statistics_unit_load_str[" << *StrHelper::Str2Wstr(str) << "]");
    return -1;
  }

  type0 = basic::PosTag::GetPosTag(*StrHelper::Str2Wstr(items[0]));
  type1 = basic::PosTag::GetPosTag(*StrHelper::Str2Wstr(items[1]));
  type2 = basic::PosTag::GetPosTag(*StrHelper::Str2Wstr(items[2]));

  bool ret = StrHelper::GetNum(items[3], count);
  if (!ret) {
    FATAL("invalid_statistics_unit_load_str_invalid_count[" 
        << *StrHelper::Str2Wstr(items[3]) 
        << "]");
    return -2;
  }
  return 0;
}

void StatisticsUnit::Dump(std::stringstream &ss) const {
  ss << *StrHelper::Wstr2Str(basic::PosTag::Str(type0)) << kSep;
  ss << *StrHelper::Wstr2Str(basic::PosTag::Str(type1)) << kSep;
  ss << *StrHelper::Wstr2Str(basic::PosTag::Str(type2)) << kSep;
  ss << count;
}

}}}
