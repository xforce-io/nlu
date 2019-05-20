#pragma once

#include "../../public.h"
#include "feature_comb.h"

namespace xforce { namespace nlu { namespace pos {

class WindowFeature {
 public:
  virtual bool ExtractFeature(IN const std::wstring &word, OUT std::wstring &feature) = 0;
  static bool IsWord(const std::wstring &feature) { return feature.at(0) != '_'; }
};

class WindowFeatureSelf : public WindowFeature {
 public:
  inline bool ExtractFeature(const std::wstring &word, std::wstring &feature);
};

class WindowFeatureIsVerb : public WindowFeature{
 public:
  static const std::wstring kMark;

 public:
  inline bool ExtractFeature(const std::wstring &word, std::wstring &feature);
};

class WindowFeatureIsNoun : public WindowFeature{
 public:
  static const std::wstring kMark;

 public:
  inline bool ExtractFeature(const std::wstring &word, std::wstring &feature);
};

class WindowFeatureWildcard : public WindowFeature{
 public:
  static const std::wstring kMark;

 public:
  inline bool ExtractFeature(const std::wstring &word, std::wstring &feature);
};

class WindowFeaturesExtractor {
 public:
  WindowFeaturesExtractor();

  void ExtractFeature(const std::wstring &word, std::vector<std::wstring> &feature);

  void Enum(
          const std::wstring &word0,
          const std::wstring &word1,
          std::vector<FeatureComb3> &results) const;

  void Enum(
          const std::wstring &word0,
          const std::wstring &word1,
          const std::wstring &word2,
          std::vector<FeatureComb3> &results) const;

 private:
  std::vector<std::shared_ptr<WindowFeature>> windowFeatures_;
};

}}}