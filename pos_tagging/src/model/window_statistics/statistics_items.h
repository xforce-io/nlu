#pragma once

#include "../../public.h"
#include "statistics_unit.h"

namespace xforce { namespace nlu { namespace pos {

class StatisticsItems {
 public:
  enum Category {
    kCategory0,
    kCategory1,
    kCategory2,
    kCategory01,
    kCategory12,
    kCategory02,
    kCategory012,
    kOther,
  };

 private:
  static const char kSep = ':';
  static const int kThresholdCnt;
  static const double kThresholdLeader;

 public:
  StatisticsItems();
  virtual ~StatisticsItems() {}

  virtual StatisticsItems::Category GetCategory() const = 0;
  void Add(const StatisticsUnit &newItem);
  size_t Size() const { return statisticsItems_.size(); }
  size_t GetCount() const { return count_; }
  const StatisticsUnit* GetDominator();
  bool operator==(const StatisticsItems &other) const;

  static StatisticsItems* Load(const std::string &str);
  void Dump(std::stringstream &ss) const;

 protected:
  virtual bool IsValid_(const StatisticsUnit &one) = 0;
  virtual bool Match_(const StatisticsUnit &one, const StatisticsUnit &other) = 0;

 private:
  std::list<StatisticsUnit> statisticsItems_;
  size_t count_;
};

class StatisticsItems0 : public StatisticsItems {
 public:
  StatisticsItems::Category GetCategory() const { return kCategory0; }

 protected:
  inline bool IsValid_(const StatisticsUnit &one);
  inline bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItems1 : public StatisticsItems {
 public:
  StatisticsItems::Category GetCategory() const { return kCategory1; }

 protected:
  inline bool IsValid_(const StatisticsUnit &one);
  inline bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItems2 : public StatisticsItems {
 public:
  StatisticsItems::Category GetCategory() const { return kCategory2; }

 protected:
  inline bool IsValid_(const StatisticsUnit &one);
  inline bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItems01 : public StatisticsItems {
 public:
  StatisticsItems::Category GetCategory() const { return kCategory01; }

 protected:
  inline bool IsValid_(const StatisticsUnit &one);
  inline bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItems12 : public StatisticsItems {
 public:
  StatisticsItems::Category GetCategory() const { return kCategory12; }

 protected:
  inline bool IsValid_(const StatisticsUnit &one);
  inline bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItems02 : public StatisticsItems {
 public:
  StatisticsItems::Category GetCategory() const { return kCategory02; }

 protected:
  inline bool IsValid_(const StatisticsUnit &one);
  inline bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItems012 : public StatisticsItems {
 public:
  StatisticsItems::Category GetCategory() const { return kCategory012; }

 protected:
  inline bool IsValid_(const StatisticsUnit &one);
  inline bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

bool StatisticsItems0::IsValid_(const StatisticsUnit &one) {
  return one.type0 != basic::PosTag::Type::kUndef;
}

bool StatisticsItems0::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type0 == other.type0;
}

bool StatisticsItems1::IsValid_(const StatisticsUnit &one) {
  return one.type1 != basic::PosTag::Type::kUndef;
}

bool StatisticsItems1::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type1 == other.type1;
}

bool StatisticsItems2::IsValid_(const StatisticsUnit &one) {
  return one.type2 != basic::PosTag::Type::kUndef;
}

bool StatisticsItems2::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type2 == other.type2;
}

bool StatisticsItems01::IsValid_(const StatisticsUnit &one) {
  return one.type0 != basic::PosTag::Type::kUndef &&
      one.type1 != basic::PosTag::Type::kUndef;
}

bool StatisticsItems01::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type0 == other.type0 && one.type1 == other.type1;
}

bool StatisticsItems12::IsValid_(const StatisticsUnit &one) {
  return one.type1 != basic::PosTag::Type::kUndef &&
      one.type2 != basic::PosTag::Type::kUndef;
}

bool StatisticsItems12::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type1 == other.type1 && one.type2 == other.type2;
}

bool StatisticsItems02::IsValid_(const StatisticsUnit &one) {
  return one.type0 != basic::PosTag::Type::kUndef &&
      one.type2 != basic::PosTag::Type::kUndef;
}

bool StatisticsItems02::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type0 == other.type0 && one.type2 == other.type2;
}

bool StatisticsItems012::IsValid_(const StatisticsUnit &one) {
  return one.type0 != basic::PosTag::Type::kUndef &&
      one.type1 != basic::PosTag::Type::kUndef &&
      one.type2 != basic::PosTag::Type::kUndef;
}

bool StatisticsItems012::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type0 == other.type0 &&
      one.type1 == other.type1 &&
      one.type2 == other.type2;
}

}}}
