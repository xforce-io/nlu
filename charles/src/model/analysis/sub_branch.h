#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause;

class SubBranch {
 public:
  SubBranch(
          const basic::Chunk &chunk,
          std::shared_ptr<AnalysisClause> clause);

  const basic::Chunk& GetChunk() const { return chunk_; }
  const AnalysisClause& GetClause() const { return *clause_; }

 private:
  basic::Chunk chunk_;
  std::shared_ptr<AnalysisClause> clause_;
};

}}}
