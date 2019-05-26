#include "../window_feature.h"

namespace xforce { namespace nlu { namespace pos {

const std::wstring WindowFeatureIsVerb::kMark = L"_v_";
const std::wstring WindowFeatureIsNoun::kMark = L"_n_";
const std::wstring WindowFeatureWildcard::kMark = L"__";

bool WindowFeatureSelf::ExtractFeature(const std::wstring &word, std::wstring &feature) {
  feature = word;
  return true;
}

bool WindowFeatureIsVerb::ExtractFeature(const std::wstring &word, std::wstring &feature) {
  auto poses = basic::Manager::Get().GetGkb().GetGkbGlobal().GetPosTags(word);
  if (poses == nullptr) {
    return false;
  }

  for (auto &pos : *poses) {
    if (basic::PosTag::kV != pos && basic::PosTag::kVn != pos) {
      return false;
    }
  }
  feature = kMark;
  return true;
}

bool WindowFeatureIsNoun::ExtractFeature(const std::wstring &word, std::wstring &feature) {
  auto poses = basic::Manager::Get().GetGkb().GetGkbGlobal().GetPosTags(word);
  if (poses == nullptr) {
    return false;
  }

  for (auto &pos : *poses) {
    if (basic::PosTag::kN != pos) {
      return false;
    }
  }
  feature = kMark;
  return true;
}

bool WindowFeatureWildcard::ExtractFeature(const std::wstring &word, std::wstring &feature) {
  feature = kMark;
  return true;
}

WindowFeaturesExtractor::WindowFeaturesExtractor() {
  windowFeatures_.push_back(std::make_shared<WindowFeatureSelf>());
  windowFeatures_.push_back(std::make_shared<WindowFeatureIsVerb>());
  windowFeatures_.push_back(std::make_shared<WindowFeatureIsNoun>());
}

void WindowFeaturesExtractor::ExtractFeature(const std::wstring &word, std::vector<std::wstring> &features) {
  std::wstring tmpFeature;
  for (auto &windowFeature : windowFeatures_) {
    if (windowFeature->ExtractFeature(word, tmpFeature)) {
      features.push_back(tmpFeature);
    }
  }
}

void WindowFeaturesExtractor::Enum(
        const std::wstring &word0,
        const std::wstring &word1,
        std::vector<FeatureComb3> &results) const {
  std::wstring tmpFeature;
  std::vector<std::wstring> features0;
  for (auto &windowFeature : windowFeatures_) {
    bool ret = windowFeature->ExtractFeature(word0, tmpFeature);
    if (ret) {
      features0.push_back(tmpFeature);
    }
  }

  std::vector<std::wstring> features1;
  for (auto &windowFeature : windowFeatures_) {
    bool ret = windowFeature->ExtractFeature(word1, tmpFeature);
    if (ret) {
      features1.push_back(tmpFeature);
    }
  }

  for (auto &feature0 : features0) {
    for (auto &feature1 : features1) {
      if (WindowFeature::IsWord(feature0) ||
          WindowFeature::IsWord(feature1)) {
        results.push_back(FeatureComb3(feature0, feature1));
      }
    }
  }
}

void WindowFeaturesExtractor::Enum(
        const std::wstring &word0,
        const std::wstring &word1,
        const std::wstring &word2,
        std::vector<FeatureComb3> &results) const {
  std::wstring tmpFeature;
  std::vector<std::wstring> features0;
  for (auto &windowFeature : windowFeatures_) {
    bool ret = windowFeature->ExtractFeature(word0, tmpFeature);
    if (ret && tmpFeature != WindowFeatureWildcard::kMark) {
      features0.push_back(tmpFeature);
    }
  }

  std::vector<std::wstring> features1;
  for (auto &windowFeature : windowFeatures_) {
    bool ret = windowFeature->ExtractFeature(word1, tmpFeature);
    if (ret) {
      features1.push_back(tmpFeature);
    }
  }

  std::vector<std::wstring> features2;
  for (auto &windowFeature : windowFeatures_) {
    bool ret = windowFeature->ExtractFeature(word2, tmpFeature);
    if (ret && tmpFeature != WindowFeatureWildcard::kMark) {
      features2.push_back(tmpFeature);
    }
  }

  for (auto &feature0 : features0) {
    for (auto &feature1 : features1) {
      for (auto &feature2 : features2) {
        if (WindowFeature::IsWord(feature0) ||
            WindowFeature::IsWord(feature1) ||
            WindowFeature::IsWord(feature2)) {
          results.push_back(FeatureComb3(feature0, feature1, feature2));
        }
      }
    }
  }
}

}}}
