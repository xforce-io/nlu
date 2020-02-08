#include "../analysis_cache.h"
#include "../analysis_clause.h"

namespace xforce { namespace nlu { namespace charles {

AnalysisCache AnalysisCache::analysisCache_;

void AnalysisCache::Set(
        std::shared_ptr<AnalysisClause> analysisClause) {
  container_.insert(std::make_pair(
          std::make_pair(analysisClause->GetClause()->GetQuery(), analysisClause->GetTheEndTag()),
          analysisClause));
}

}}}