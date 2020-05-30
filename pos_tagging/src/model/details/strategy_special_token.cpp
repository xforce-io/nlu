#include "../strategy_special_token.h"

namespace xforce { namespace nlu { namespace pos {

void StrategySpecialToken::Process(basic::NluContext &nluContext) {
  Strategy::Process(nluContext);

  for (auto &segment : nluContext.Get<basic::Segment>().GetAll()) {
    if (!segment->GetTags().empty()) {
      continue;
    }

    auto &segStr = segment->GetStrFromSentence(nluContext.GetQuery());
    for (size_t i=0; i < segStr.length(); ++i) {
      wchar_t c = segStr[i];
      bool isLetter = (c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z');
      bool isNum = (c >= L'0' && c <= L'9');
      if (isLetter) {
        segment->AddTag(basic::PosTag::Type::kN);
        break;
      } else if (isNum) {
        segment->AddTag(basic::PosTag::Type::kM);
        break;
      }
    }
  }
}

}}}
