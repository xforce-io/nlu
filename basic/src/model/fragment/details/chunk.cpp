#include "../chunk.h"
#include "../../../data/manager.h"
#include "../../../data/gkb/gkb.h"
#include "../../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

std::shared_ptr<Segment> Chunk::FindSeg(
        const NluContext &nluContext,
        basic::PosTag::Type::Val posTag) {
  for (auto &seg : nluContext.Get<Segment>().GetAll()) {
    if (seg->GetBegin() >= GetBegin() &&
        seg->GetEnd() <= GetEnd() &&
        seg->GetTag() == posTag) {
      return seg;
    }
  }
  return nullptr;
}

void Chunk::Dump(JsonType &jsonType) const {
  Super::Dump(jsonType);
  jsonType["type"] = "chunk";
  for (auto &syntaxTag : tags_) {
    jsonType["syn"].Append(*(StrHelper::Wstr2Str(SyntaxTag::Str(syntaxTag))));
  }
}


void Chunk::AddTagForCtx(
      const NluContext &nluContext,
      Chunk &chunk,
      SyntaxTag::Type::Val tag) {
  if (SyntaxTag::Type::kV == tag) {
    std::shared_ptr<Segment> theVerb;
    for (auto &segment : nluContext.Get<Segment>().GetAll()) {
      if (chunk.GetOffset() <= segment->GetOffset()
          && segment->GetEnd() <= chunk.GetEnd()
          && segment->GetTag() == PosTag::Type::kV) {
        theVerb = segment;
      }
    }

    if (theVerb != nullptr) { // maybe rp
      std::wstring word = theVerb->GetStrFromSentence(nluContext.GetQuery());
      bool isZhu = Manager::Get().GetGkb().GetGkbVerb().IsZhu(word);
      if (isZhu) {
        chunk.AddTag(SyntaxTag::Type::kVw);
      }
    }

    if (chunk.tags_.empty()) {
      auto segment = chunk.FindSeg(nluContext, PosTag::Type::kV);
      if (nullptr != segment) {
        auto seg = segment->GetQuery(nluContext.GetQuery());
        bool ret = Manager::Get().GetGkb().GetGkbVerb().TiWeiZhun(
                seg,
                chunk.isArgTi_,
                chunk.isArgWei_,
                chunk.isArgZhun_);
        if (ret) {
          chunk.verbArgInfo_ = true;
        }
      }
    } else {
      chunk.verbArgInfo_ = false;
    }
  }
  chunk.AddTag(tag);
}

}}}
