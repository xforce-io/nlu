#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace pos {

struct StatisticsUnit {
 private:
  static const char kSep = ',';

 public:
  inline StatisticsUnit();

  inline StatisticsUnit(
      basic::PosTag::Type::Val type0,
      basic::PosTag::Type::Val type1);

  inline StatisticsUnit(
      basic::PosTag::Type::Val type0,
      basic::PosTag::Type::Val type1,
      basic::PosTag::Type::Val type2);

  inline bool SameType(const StatisticsUnit &other) const;
  inline bool operator==(const StatisticsUnit &other) const;

  void CalcConfidence(size_t totalCnt);

  int Load(const std::string &str);
  void Dump(std::stringstream &ss) const;

 public:
  basic::PosTag::Type::Val type0;
  basic::PosTag::Type::Val type1;
  basic::PosTag::Type::Val type2;
  size_t count;
  basic::Confidence confidence;
};

StatisticsUnit::StatisticsUnit() :
        type0(basic::PosTag::Type::kUndef),
        type1(basic::PosTag::Type::kUndef),
        type2(basic::PosTag::Type::kUndef),
        count(0) {}

StatisticsUnit::StatisticsUnit(
        basic::PosTag::Type::Val type0Arg,
        basic::PosTag::Type::Val type1Arg) :
        type0(type0Arg),
        type1(type1Arg),
        type2(basic::PosTag::Type::kUndef),
        count(1) {}

StatisticsUnit::StatisticsUnit(
        basic::PosTag::Type::Val type0Arg,
        basic::PosTag::Type::Val type1Arg,
        basic::PosTag::Type::Val type2Arg) :
        type0(type0Arg),
        type1(type1Arg),
        type2(type2Arg),
        count(1) {}

bool StatisticsUnit::SameType(const StatisticsUnit &other) const {
  return type0 == other.type0 &&
         type1 == other.type1 &&
         type2 == other.type2;
}

bool StatisticsUnit::operator==(const StatisticsUnit &other) const {
  return SameType(other) && count == other.count;
}

}}}
