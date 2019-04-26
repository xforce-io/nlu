#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace pos {

struct StatisticsUnit {
 public:
  inline StatisticsUnit();

  inline StatisticsUnit(
      basic::PosTag::Type type0,
      basic::PosTag::Type type1);

  inline StatisticsUnit(
      basic::PosTag::Type type0,
      basic::PosTag::Type type1,
      basic::PosTag::Type type2);

  inline bool SameType(const StatisticsUnit &statisticsItem) const;

 public:
  basic::PosTag::Type type0;
  basic::PosTag::Type type1;
  basic::PosTag::Type type2;
  size_t count;
};

StatisticsUnit::StatisticsUnit() :
        type0(basic::PosTag::kUndef),
        type1(basic::PosTag::kUndef),
        type2(basic::PosTag::kUndef),
        count(0) {}


StatisticsUnit::StatisticsUnit(
        basic::PosTag::Type type0Arg,
        basic::PosTag::Type type1Arg) :
        type0(type0Arg),
        type1(type1Arg),
        type2(basic::PosTag::kUndef),
        count(1) {}

StatisticsUnit::StatisticsUnit(
        basic::PosTag::Type type0Arg,
        basic::PosTag::Type type1Arg,
        basic::PosTag::Type type2Arg) :
        type0(type0Arg),
        type1(type1Arg),
        type2(type2Arg),
        count(1) {}

bool StatisticsUnit::SameType(const StatisticsUnit &other) const {
  return type0 == other.type0 &&
         type1 == other.type1 &&
         type2 == other.type2;
}

}}}
