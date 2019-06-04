#include "../statistics_unit.h"

namespace xforce { namespace nlu { namespace pos {

void StatisticsUnit::Dump(std::stringstream &ss) const {
  ss << *StrHelper::Wstr2Str(basic::PosTag::Str(type0)) << ',';
  ss << *StrHelper::Wstr2Str(basic::PosTag::Str(type1)) << ',';
  ss << *StrHelper::Wstr2Str(basic::PosTag::Str(type2)) << ',';
  ss << count;
}

}}}
