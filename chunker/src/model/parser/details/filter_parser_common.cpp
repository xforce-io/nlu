#include "../filter_parser_common.h"

namespace xforce { namespace nlu { namespace chunker {

void FPCDongjieAndDongqu::Filter(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next,
        int &chunkPos,
        basic::SyntaxTag::Type::Val &syntaxTag) {
  if (nullptr == next) {
    return;
  }

  std::wstring curStr = cur->GetStrFromSentence(nluContext.GetQuery());
  std::wstring nextStr = next->GetStrFromSentence(nluContext.GetQuery());
  if (cur->GetTag() == basic::PosTag::Type::kV) {
    if (basic::Manager::Get().GetGkb().GetGkbVerb().IsDongjieOrDongquPhrase(curStr, nextStr)) {
      chunkPos = -3;
      syntaxTag = basic::SyntaxTag::Type::kV;
      return;
    } else if (L"得" == nextStr) {
      for (auto &segment : nluContext.GetSegments().GetAll()) {
        if (segment->GetOffset() < next->GetOffset() + next->GetLen()) {
          continue;
        }

        if (segment->GetTag() == basic::PosTag::Type::kD ||
            L"的" == segment->GetStrFromSentence(nluContext.GetQuery())) {
          continue;
        } else {
          if (basic::Manager::Get().GetGkb().GetGkbVerb().IsDongjieOrDongquPhrase(curStr, nextStr) ||
              segment->GetTag() == basic::PosTag::Type::kA) {
            chunkPos = SCAST<int>(segment->GetOffset() + segment->GetLen() - cur->GetOffset());
            syntaxTag = basic::SyntaxTag::Type::kV;
            return;
          }
        }
      }
    }
  }
}

void FPCMid::Filter(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next,
        int &chunkPos,
        basic::SyntaxTag::Type::Val &syntaxTag) {
  UNUSE(nluContext)
  UNUSE(syntaxTag)

  if (nullptr == next) {
    return;
  }

  auto curClassOfPosTags = cur->GetClassOfPosTags();
  auto nextClassOfPosTags = next->GetClassOfPosTags();
  if (basic::PosTag::Class::kUndef == curClassOfPosTags ||
      basic::PosTag::Class::kUndef == nextClassOfPosTags) {
    return;
  }

  if (basic::PosTag::Class::kNominal == curClassOfPosTags &&
      (basic::PosTag::Class::kPredicate == nextClassOfPosTags ||
       basic::PosTag::Class::kAdv == nextClassOfPosTags)) {
    chunkPos = -2;
    return;
  } else if ((basic::PosTag::Class::kPredicate == curClassOfPosTags ||
              basic::PosTag::Class::kAdv == curClassOfPosTags) &&
             basic::PosTag::Class::kNominal == nextClassOfPosTags) {
    chunkPos = -2;
    return;
  } else if (basic::PosTag::Class::kPredicate == curClassOfPosTags &&
             basic::PosTag::Class::kAdv == nextClassOfPosTags) {
    chunkPos = -2;
    return;
  }
}

void FPCSurround::Filter(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> cur,
        std::shared_ptr<basic::Segment> next,
        int &chunkPos,
        basic::SyntaxTag::Type::Val &syntaxTag) {
  UNUSE(nluContext)
  UNUSE(next)
  UNUSE(syntaxTag)

  auto curClassOfPosTags = cur->GetClassOfPosTags();
  if (basic::PosTag::Class::kUndef == curClassOfPosTags) {
    return;
  }

  if (basic::PosTag::Class::kFuncWord == curClassOfPosTags ||
      basic::PosTag::Class::kMood == curClassOfPosTags ||
      basic::PosTag::Class::kTime == curClassOfPosTags ||
      basic::PosTag::Class::kPunctuation == curClassOfPosTags) {
    chunkPos = -1;
    return;
  }
}

}}}
