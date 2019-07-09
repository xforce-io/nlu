#pragma once

#include "public.h"
#include "analysis_component.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause : public AnalysisComponent {
 public:
  enum Stage {
      kNone,
      kSegment,
      kPosTag,
      kChunk,
      kSyntax,
      kEnd,
  };

 public:
  AnalysisClause(
          const std::wstring &clause);

  AnalysisClause(
          const std::wstring &clause,
          bool isMaster);

  void Process();

  std::shared_ptr<AnalysisClause> Clone();

  void Dump(JsonType &jsonType);

 private:
  bool isMaster_;
  std::shared_ptr<basic::NluContext> nluContext_;
  std::unordered_map<Stage, std::shared_ptr<AnalysisClause>> ancestors_;
};

}}}
