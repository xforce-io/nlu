#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause;

class AnalysisCache {
 private:
  struct HashAnalysisCache {
      size_t operator()(
              const std::pair<
                      std::wstring,
                      std::shared_ptr<basic::CollectionSyntaxTag>> &x) const {
        return std::hash<std::wstring>()(x.first);
      }
  };

 public:
  typedef std::unordered_map<
          std::pair<std::wstring, std::shared_ptr<basic::CollectionSyntaxTag>>,
          std::shared_ptr<AnalysisClause>,
          HashAnalysisCache> Container;

 public:
  inline std::shared_ptr<AnalysisClause> Get(
          std::pair<std::wstring, std::shared_ptr<basic::CollectionSyntaxTag>> key);

  void Set(
          std::shared_ptr<AnalysisClause> analysisClause);

  static AnalysisCache& Get() { return analysisCache_; }

 private:
  Container container_;

  static AnalysisCache analysisCache_;
};

std::shared_ptr<AnalysisClause> AnalysisCache::Get(
        std::pair<std::wstring, std::shared_ptr<basic::CollectionSyntaxTag>> key) {
  auto iter = container_.find(key);
  return iter != container_.end() ? iter->second : nullptr;
}

}}}