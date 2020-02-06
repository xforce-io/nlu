#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause;

class AnalysisCache {
 public:
  typedef std::unordered_map<std::wstring, std::shared_ptr<AnalysisClause>> Container;

 public:
  inline std::shared_ptr<AnalysisClause> Get(const std::wstring &key);
  inline void Set(const std::wstring &key, std::shared_ptr<AnalysisClause> analysisClause);

  static AnalysisCache& Get() { return analysisCache_; }

 private:
  Container container_;

  static AnalysisCache analysisCache_;
};

std::shared_ptr<AnalysisClause> AnalysisCache::Get(const std::wstring &key) {
  auto iter = container_.find(key);
  return iter != container_.end() ? iter->second : nullptr;
}

void AnalysisCache::Set(const std::wstring &key, std::shared_ptr<AnalysisClause> analysisClause) {
  container_.insert(std::make_pair(key, analysisClause));
}

}}}