#pragma once

#include "public.h"
#include "analysis_component.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClause : public AnalysisComponent {
 public:
  AnalysisClause(
          const std::wstring &clause);

  AnalysisClause(
          const std::wstring &clause,
          bool isMaster);

  bool Process(std::vector<std::shared_ptr<AnalysisClause>> &children);

  std::shared_ptr<AnalysisClause> Clone();

  void Dump(JsonType &jsonType);

 private:
  static bool IsFinished_(basic::NluContext &nluContext);

 private:
  bool isMaster_;
  std::shared_ptr<basic::NluContext> nluContext_;
  std::unordered_map<basic::Stage::Type, std::shared_ptr<AnalysisClause>> ancestors_;
};

}}}
