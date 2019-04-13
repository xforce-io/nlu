#include "../strategy_window_statistics.h"
#include "../window_statistics.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace pos {

const double StatisticsItems::kThresholdLeader = 0.95;

const StatisticsItem* StatisticsItems::GetDominator() const {
  for (auto const &statisticsItem : statisticsItems_) {
    if (statisticsItem.count * 1.0 / count_ > kThresholdLeader) {
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
    auto statisticsItems = windowStatistics_->Get(
            segments[i]->GetStrFromSentence(nluContext.GetQuery()),
            segments[i+1]->GetStrFromSentence(nluContext.GetQuery())
            );
    if (nullptr != statisticsItems) {
      auto dominator = statisticsItems->GetDominator();
      if (dominator != nullptr) {
        nluContext.GetSegments()[i]->SetPosTag(dominator->type0);
        nluContext.GetSegments()[i]->SetStrategy(Strategy::kStrategyWindowStatistics);

        nluContext.GetSegments()[i+1]->SetPosTag(dominator->type1);
        nluContext.GetSegments()[i+1]->SetStrategy(Strategy::kStrategyWindowStatistics);
      }
    }
  }

  for (size_t i=0; i < lenSegments-2; ++i) {
    auto statisticsItems = windowStatistics_->Get(
            segments[i]->GetStrFromSentence(nluContext.GetQuery()),
            segments[i+1]->GetStrFromSentence(nluContext.GetQuery()),
            segments[i+2]->GetStrFromSentence(nluContext.GetQuery())
            );
    if (nullptr != statisticsItems) {
      auto dominator = statisticsItems->GetDominator();
      if (dominator != nullptr) {
        nluContext.GetSegments()[i]->SetPosTag(dominator->type0);
        nluContext.GetSegments()[i]->SetStrategy(Strategy::kStrategyWindowStatistics);

        nluContext.GetSegments()[i+1]->SetPosTag(dominator->type1);
        nluContext.GetSegments()[i+1]->SetStrategy(Strategy::kStrategyWindowStatistics);

        nluContext.GetSegments()[i+2]->SetPosTag(dominator->type2);
        nluContext.GetSegments()[i+2]->SetStrategy(Strategy::kStrategyWindowStatistics);
      }
    }
  }
}

}}}
