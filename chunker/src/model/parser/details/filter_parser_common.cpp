#include "../filter_parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

ParserCommon::ChunkPos FPCDongqu::Filter(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next) {
  if (nullptr == next) {
    return ParserCommon::kUndef;
  }

  std::wstring curStr = cur->GetStrFromSentence(nluContext.GetQuery());
  std::wstring nextStr = next->GetStrFromSentence(nluContext.GetQuery());
  if (cur->GetTag() == basic::PosTag::Type::kV &&
      basic::Manager::Get().GetGkb().GetGkbVerb().IsPhrase(curStr, nextStr)) {
    return ParserCommon::k02;
  }
  return ParserCommon::kUndef;
}

ParserCommon::ChunkPos FPCMid::Filter(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next) {
  UNUSE(nluContext)

  if (nullptr == next) {
    return ParserCommon::kUndef;
  }

  auto curClassOfPosTags = cur->GetClassOfPosTags();
  auto nextClassOfPosTags = next->GetClassOfPosTags();
  if (basic::PosTag::Class::kUndef == curClassOfPosTags ||
      basic::PosTag::Class::kUndef == nextClassOfPosTags) {
    return ParserCommon::kUndef;
  }

  if (basic::PosTag::Class::kNominal == curClassOfPosTags &&
      (basic::PosTag::Class::kPredicate == nextClassOfPosTags ||
       basic::PosTag::Class::kAdv == nextClassOfPosTags)) {
    return ParserCommon::k1;
  } else if ((basic::PosTag::Class::kPredicate == curClassOfPosTags ||
              basic::PosTag::Class::kAdv == curClassOfPosTags) &&
             basic::PosTag::Class::kNominal == nextClassOfPosTags) {
    return ParserCommon::k1;
  } else if (basic::PosTag::Class::kPredicate == curClassOfPosTags &&
             basic::PosTag::Class::kAdv == nextClassOfPosTags) {
    return ParserCommon::k1;
  }
  return ParserCommon::kUndef;
}

ParserCommon::ChunkPos FPCSurround::Filter(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next) {
  UNUSE(nluContext)
  UNUSE(next)

  auto curClassOfPosTags = cur->GetClassOfPosTags();
  if (basic::PosTag::Class::kUndef == curClassOfPosTags) {
    return ParserCommon::kUndef;
  }

  if (basic::PosTag::Class::kFuncWord == curClassOfPosTags ||
      basic::PosTag::Class::kMood == curClassOfPosTags ||
      basic::PosTag::Class::kPunctuation == curClassOfPosTags) {
    return ParserCommon::k01;
  }
  return ParserCommon::kUndef;
}

}}}
