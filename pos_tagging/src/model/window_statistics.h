#include "../public.h"

namespace xforce { namespace nlu { namespace pos {

struct StatisticsItem {
 public:
  inline StatisticsItem();
  inline StatisticsItem(
          basic::PosTag::Type type0,
          basic::PosTag::Type type1);
  inline StatisticsItem(
          basic::PosTag::Type type0,
          basic::PosTag::Type type1,
          basic::PosTag::Type type2);

  inline bool SameType(const StatisticsItem &statisticsItem) const;

 public:
  basic::PosTag::Type type0;
  basic::PosTag::Type type1;
  basic::PosTag::Type type2;
  size_t count;
};

class StatisticsItems {
 private:
  static const double kThresholdLeader;

 public:
  inline void Add(const StatisticsItem &statisticsItem);
  inline const StatisticsItem& operator[](size_t i) const;
  const std::vector<StatisticsItem>& GetItems() const { return statisticsItems_; }
  std::vector<StatisticsItem>& GetItems() { return statisticsItems_; }
  size_t GetCount() const { return count_; }
  inline size_t NumItems() const;
  const StatisticsItem* GetDominator() const;

 private:
  std::vector<StatisticsItem> statisticsItems_;
  size_t count_;
};

class WindowStatistics {
 public:
  WindowStatistics() {}
  virtual ~WindowStatistics();

 public:
  inline StatisticsItems* Get(
          const std::wstring &item0,
          const std::wstring &item1);

  inline StatisticsItems* Get(
          const std::wstring &item0,
          const std::wstring &item1,
          const std::wstring &item2);

 public:
  static WindowStatistics* Create(const std::string &filepath);

 private:
  void Add_(const std::vector<std::pair<std::wstring, basic::PosTag::Type >> &pairs);

  void ActualAdd_(const std::wstring &key, const StatisticsItem &newItem);

 private:
  std::unordered_map<std::wstring, StatisticsItems*> statistics_;
};

StatisticsItem::StatisticsItem() :
  type0(basic::PosTag::kUndef),
  type1(basic::PosTag::kUndef),
  type2(basic::PosTag::kUndef),
  count(0) {}

StatisticsItem::StatisticsItem(
        basic::PosTag::Type type0Arg,
        basic::PosTag::Type type1Arg) :
    type0(type0Arg),
    type1(type1Arg),
    type2(basic::PosTag::kUndef),
    count(1) {}

StatisticsItem::StatisticsItem(
        basic::PosTag::Type type0Arg,
        basic::PosTag::Type type1Arg,
        basic::PosTag::Type type2Arg) :
    type0(type0Arg),
    type1(type1Arg),
    type2(type2Arg),
    count(1) {}


bool StatisticsItem::SameType(const StatisticsItem &other) const {
  return type0 == other.type0 &&
    type1 == other.type1 &&
    type2 == other.type2;
}

void StatisticsItems::Add(const StatisticsItem &statisticsItem) {
  statisticsItems_.push_back(statisticsItem);
  count_ += statisticsItem.count;
}

const StatisticsItem& StatisticsItems::operator[](size_t i) const {
  return statisticsItems_[i];
}

size_t StatisticsItems::NumItems() const {
  return statisticsItems_.size();
}

StatisticsItems* WindowStatistics::Get(
        const std::wstring &item0,
        const std::wstring &item1) {
  std::wstring tmpKey = item0 + L"-" + item1;
  auto iter = statistics_.find(tmpKey);
  if (iter != statistics_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

StatisticsItems* WindowStatistics::Get(
        const std::wstring &item0,
        const std::wstring &item1,
        const std::wstring &item2) {
  std::wstring tmpKey = item0 + L"-" + item1 + L"-" + item2;
  auto iter = statistics_.find(tmpKey);
  if (iter != statistics_.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

}}}
