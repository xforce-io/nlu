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

class WindowStatistics {
 public:
  WindowStatistics() {}
  virtual ~WindowStatistics();

 private:
  typedef std::vector<StatisticsItem> StatisticsItems;

 public:
  static WindowStatistics* Create(const std::string &filepath);

 private:
  void Add_(
          const std::wstring &word0,
          const std::wstring &word1,
          basic::PosTag::Type type0,
          basic::PosTag::Type type1);

  void Add_(
          const std::wstring &word0,
          const std::wstring &word1,
          const std::wstring &word2,
          basic::PosTag::Type type0,
          basic::PosTag::Type type1,
          basic::PosTag::Type type2);

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

}}}
