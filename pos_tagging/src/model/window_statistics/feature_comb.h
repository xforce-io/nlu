#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace pos {

struct FeatureComb3 {
 public:
  inline FeatureComb3(
          const std::wstring &feature0,
          const std::wstring &feature1);

  inline FeatureComb3(
          const std::wstring &feature0,
          const std::wstring &feature1,
          const std::wstring &feature2);

  inline bool operator==(const FeatureComb3 &featureComb3) const;

 public:
  std::wstring feature0;
  std::wstring feature1;
  std::wstring feature2;
};

FeatureComb3::FeatureComb3(
        const std::wstring &feature0,
        const std::wstring &feature1) :
    FeatureComb3(feature0, feature1, L"") {}

FeatureComb3::FeatureComb3(
        const std::wstring &feature0Arg,
        const std::wstring &feature1Arg,
        const std::wstring &feature2Arg) :
    feature0(feature0Arg),
    feature1(feature1Arg),
    feature2(feature2Arg) {}

bool FeatureComb3::operator==(const FeatureComb3 &featureComb3) const {
  return feature0 == featureComb3.feature0 &&
      feature1 == featureComb3.feature1 &&
      feature2 == featureComb3.feature2;
}

}}}


