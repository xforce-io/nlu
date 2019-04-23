#pragma once

#include "../../public.h"
#include "statistics_unit.h"

namespace xforce { namespace nlu { namespace pos {

class StatisticsItems {
 private:
  static const int kThresholdCnt;
  static const double kThresholdLeader;

 public:
  void Add(const StatisticsUnit &newItem);
  inline const StatisticsUnit& operator[](size_t i) const;
  const std::vector<StatisticsUnit>& GetItems() const { return statisticsItems_; }
  std::vector<StatisticsUnit>& GetItems() { return statisticsItems_; }
  size_t Size() const { return statisticsItems_.size(); }
  size_t GetCount() const { return count_; }
  inline size_t NumItems() const;
  const StatisticsUnit* GetDominator() const;

 protected:
  virtual bool Match_(const StatisticsUnit &one, const StatisticsUnit &other) = 0;

 private:
    std::vector<StatisticsUnit> statisticsItems_;
    size_t count_;
};

class StatisticsItemsLeft : public StatisticsItems {
 protected:
  bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItemsRight : public StatisticsItems {
 protected:
  bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

class StatisticsItemsAround : public StatisticsItems {
 protected:
  bool Match_(const StatisticsUnit &one, const StatisticsUnit &other);
};

const StatisticsUnit& StatisticsItems::operator[](size_t i) const {
  return statisticsItems_[i];
}

size_t StatisticsItems::NumItems() const {
  return statisticsItems_.size();
}

bool StatisticsItemsLeft::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type0 == other.type0;
}

bool StatisticsItemsRight::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type2 == other.type2;
}

bool StatisticsItemsAround::Match_(const StatisticsUnit &one, const StatisticsUnit &other) {
  return one.type0 == other.type0 && one.type2 == other.type2;
}

}}}