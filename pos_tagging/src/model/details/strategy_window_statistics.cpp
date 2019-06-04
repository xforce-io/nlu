#include "../strategy_window_statistics.h"
#include "../window_statistics/window_statistics.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace pos {

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

  NOTICE("before_shrink[" << windowStatistics_->Size() << "]");
  windowStatistics_->Shrink();
  NOTICE("after_shrink[" << windowStatistics_->Size() << "]");
  return true;
}

void StrategyWindowStatistics::Process(basic::NluContext &nluContext) {
  auto &segments = nluContext.GetSegments().GetAll();
  auto lenSegments = segments.size();
  for (size_t i=0; i < lenSegments-1; ++i) {
    std::wstring seg0 = segments[i]->GetStrFromSentence(nluContext.GetQuery());
    std::wstring seg1 = segments[i+1]->GetStrFromSentence(nluContext.GetQuery());

    auto dominator = windowStatistics_->GetDominator(seg0, seg1);
    if (dominator.first == StatisticsItems::kOther) {
      continue;
    } if (dominator.first == StatisticsItems::kCategory0) {
      SetPos(
              nluContext.GetSegments()[i],
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory1) {
      SetPos(
              nluContext.GetSegments()[i+1],
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory01) {
      SetPos(
              nluContext.GetSegments()[i],
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              nluContext.GetSegments()[i+1],
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    }
  }

  for (size_t i=0; i < lenSegments-2; ++i) {
    std::wstring seg0 = segments[i]->GetStrFromSentence(nluContext.GetQuery());
    std::wstring seg1 = segments[i+1]->GetStrFromSentence(nluContext.GetQuery());
    std::wstring seg2 = segments[i+2]->GetStrFromSentence(nluContext.GetQuery());

    auto dominator = windowStatistics_->GetDominator(seg0, seg1,seg2);
    if (dominator.first == StatisticsItems::kOther) {
      continue;
    } if (dominator.first == StatisticsItems::kCategory0) {
      SetPos(
              nluContext.GetSegments()[i],
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory1) {
      SetPos(
              nluContext.GetSegments()[i+1],
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory2) {
      SetPos(
              nluContext.GetSegments()[i+2],
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory01) {
      SetPos(
              nluContext.GetSegments()[i],
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              nluContext.GetSegments()[i+1],
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory12) {
      SetPos(
              nluContext.GetSegments()[i+1],
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              nluContext.GetSegments()[i+2],
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory02) {
      SetPos(
              nluContext.GetSegments()[i],
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              nluContext.GetSegments()[i+2],
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory012) {
      SetPos(
              nluContext.GetSegments()[i],
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              nluContext.GetSegments()[i+1],
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              nluContext.GetSegments()[i+2],
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    }
  }
}

}}}
