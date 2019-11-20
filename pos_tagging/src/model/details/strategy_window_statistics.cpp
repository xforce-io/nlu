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

  NOTICE("window_statistics_before_shrink[" << windowStatistics_->Size() << "]");
  windowStatistics_->Shrink();
  NOTICE("window_statistics_after_shrink[" << windowStatistics_->Size() << "]");
  return true;
}

void StrategyWindowStatistics::Process(basic::NluContext &nluContext) {
  Strategy::Process(nluContext);

  auto &segments = nluContext.GetSegments().GetAll();

  auto segIter0 = segments.begin();
  auto segIter1 = segments.end();
  auto segIter2 = segments.end();
  if (segIter0 != segments.end()) {
    segIter1 = segIter0;
    ++segIter1;
    if (segIter1 != segments.end()) {
      segIter2 = segIter1;
      ++segIter2;
    }
  }

  while (segIter2 != segments.end()) {
    std::wstring seg0 = (*segIter0)->GetStrFromSentence(nluContext.GetQuery());
    std::wstring seg1 = (*segIter1)->GetStrFromSentence(nluContext.GetQuery());
    std::wstring seg2 = (*segIter2)->GetStrFromSentence(nluContext.GetQuery());

    auto dominator = windowStatistics_->GetDominator(seg0, seg1,seg2);
    if (dominator.first == StatisticsItems::kOther) {
      ++segIter0;
      ++segIter1;
      ++segIter2;
      continue;
    } else if (dominator.first == StatisticsItems::kCategory0) {
      SetPos(
              **segIter0,
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory1) {
      SetPos(
              **segIter1,
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory2) {
      SetPos(
              **segIter2,
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory01) {
      SetPos(
              **segIter0,
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              **segIter1,
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory12) {
      SetPos(
              **segIter1,
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              **segIter2,
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory02) {
      SetPos(
              **segIter0,
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              **segIter2,
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory012) {
      SetPos(
              **segIter0,
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              **segIter1,
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              **segIter2,
              dominator.second->type2,
              Strategy::kStrategyWindowStatistics);
    }

    ++segIter0;
    ++segIter1;
    ++segIter2;
  }

  segIter0 = segments.begin();
  segIter1 = segments.end();
  if (segIter0 != segments.end()) {
    segIter1 = segIter0;
    ++segIter1;
  }

  while (segIter1 != segments.end()) {
    std::wstring seg0 = (*segIter0)->GetStrFromSentence(nluContext.GetQuery());
    std::wstring seg1 = (*segIter1)->GetStrFromSentence(nluContext.GetQuery());

    auto dominator = windowStatistics_->GetDominator(seg0, seg1);
    if (dominator.first == StatisticsItems::kOther) {
      ++segIter0;
      ++segIter1;
      continue;
    } else if (dominator.first == StatisticsItems::kCategory0) {
      SetPos(
              **segIter0,
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory1) {
      SetPos(
              **segIter1,
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    } else if (dominator.first == StatisticsItems::kCategory01) {
      SetPos(
              **segIter0,
              dominator.second->type0,
              Strategy::kStrategyWindowStatistics);
      SetPos(
              **segIter1,
              dominator.second->type1,
              Strategy::kStrategyWindowStatistics);
    }

    ++segIter0;
    ++segIter1;
  }
}

}}}
