#pragma once

#include "public.h"
#include "analysis_component.h"

namespace xforce { namespace nlu { namespace charles {

class AnalysisClauseBranch {
 public:
  AnalysisClauseBranch(const std::wstring &clause);
  AnalysisClauseBranch(const basic::NluContext &nluContext);

  bool Process(std::queue<std::shared_ptr<AnalysisClauseBranch>> &children);
  std::shared_ptr<AnalysisClauseBranch> Clone() const;

  void Dump(JsonType &jsonType);

 private:
  static bool IsFinished_(basic::NluContext &nluContext);

 private:
  std::shared_ptr<basic::NluContext> nluContext_;
  std::unordered_map<basic::Stage::Val, std::shared_ptr<AnalysisClauseBranch>> ancestors_;
};

}}}