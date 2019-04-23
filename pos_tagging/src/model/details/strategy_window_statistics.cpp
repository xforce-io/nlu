#include "../strategy_window_statistics.h"
#include "../window_statistics.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace pos {

const int StatisticsItems::kThresholdCnt = 3;
const double StatisticsItems::kThresholdLeader = 0.95;

const StatisticsItem* StatisticsItems::GetDominator() const {
  for (auto const &statisticsItem : statisticsItems_) {
    if (count_ >= kThresholdCnt && statisticsItem.count * 1.0 / count_ > kThresholdLeader) {
      return &statisticsItem;
    }
  }
  return nullptr;
}

StrategyWindowStatistics::StrategyWindowStatistics() :
  Strategy(),
  windowStatistics_(nullptr) {}

StrategyWindowStatistics::~StrategyWindowStatistics() {
  XFC_DELETE(windowStatistics_)
}

bool StrategyWindowStatistics::Init() {
  windowStatistics_ = WindowStatistics::Create(Conf::Get().GetLabeledDataPath());
  if (nullptr == windowStatistics_) {
    FATAL("fail_create_window_statistics");
    return false;
  }
  return true;
}

void StrategyWindowStatistics::Process(basic::NluContext &nluContext) {
  auto &segments = nluContext.GetSegments().GetAll();
  auto lenSegments = segments.size();
  for (size_t i=0; i < lenSegments-1; ++i) {
    auto seg0 = segments[i]->GetStrFromSentence(nluContext.GetQuery());
    auto seg1 = segments[i+1]->GetStrFromSentence(nluContext.GetQuery());
    auto statisticsItems = windowStatistics_->Get(seg0, seg1);
    if (nullptr != statisticsItems) {
      auto dominator = statisticsItems->GetDominator();
      if (dominator != nullptr) {
        SetPos(
                nluContext.GetSegments()[i],
                dominator->type0,
                Strategy::kStrategyWindowStatistics);

        SetPos(
                nluContext.GetSegments()[i+1],
                dominator->type1,
                Strategy::kStrategyWindowStatistics);
      }
    }
  }

  for (size_t i=0; i < lenSegments-2; ++i) {
    auto seg0 = segments[i]->GetStrFromSentence(nluContext.GetQuery());
    auto seg1 = segments[i+1]->GetStrFromSentence(nluContext.GetQuery());
    auto seg2 = segments[i+2]->GetStrFromSentence(nluContext.GetQuery());
    auto statisticsItems = windowStatistics_->Get(seg0, seg1, seg2);
    if (nullptr != statisticsItems) {
      auto dominator = statisticsItems->GetDominator();
      if (dominator != nullptr) {
        SetPos(
                nluContext.GetSegments()[i],
                dominator->type0,
                Strategy::kStrategyWindowStatistics);

        SetPos(nluContext.GetSegments()[i+1],
                dominator->type1,
                Strategy::kStrategyWindowStatistics);

        SetPos(
                nluContext.GetSegments()[i+2],
                dominator->type2,
                Strategy::kStrategyWindowStatistics);
      }
    }
  }
}

}}}
