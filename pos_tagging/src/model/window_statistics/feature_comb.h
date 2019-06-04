#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace pos {

struct FeatureComb3 {
 private:
  static const char kSep = '~';

 public:
  inline FeatureComb3(
          const std::wstring &feature0,
          const std::wstring &feature1);

  inline FeatureComb3(
          const std::wstring &feature0,
          const std::wstring &feature1,
          const std::wstring &feature2);

  inline bool operator==(const FeatureComb3 &featureComb3) const;

  void Dump(std::stringstream &ss) const;

 public:
  std::wstring feature0;
  std::wstring feature1;
  std::wstring feature2;
};

struct HashFeatureComb3 {
 public: 
  inline size_t operator()(const FeatureComb3 &featureComb3) const;

 private: 
  static std::hash<std::wstring> hashFunc;
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

size_t HashFeatureComb3::operator()(const FeatureComb3 &featureComb3) const {
  return hashFunc(featureComb3.feature0) * 37 + 
    hashFunc(featureComb3.feature1) * 13 + 
    hashFunc(featureComb3.feature2);
}

}}}


