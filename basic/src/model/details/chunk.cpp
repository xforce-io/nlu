#include "../chunk.h"
#include "../../data/manager.h"
#include "../../data/gkb/gkb.h"
#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

const std::string& Chunk::GetCategory() const {
  static const std::string kCategory = "chunk";
  return kCategory;
}

void Chunk::Dump(JsonType &jsonType) const {
  Super::Dump(jsonType);
  jsonType["type"] = "chunk";
  for (auto &syntaxTag : tags_) {
    jsonType["syn"].Append(*(StrHelper::Wstr2Str(SyntaxTag::Str(syntaxTag))));
  }
}

std::shared_ptr<Segment> Chunk::FindSeg_(
        const NluContext &nluContext,
        basic::PosTag::Type::Val posTag) {
  for (auto &seg : nluContext.GetSegments().GetAll()) {
    if (seg->GetBegin() >= GetBegin() &&
        seg->GetEnd() <= GetEnd() &&
        seg->GetTag() == posTag) {
      return seg;
    }
  }
  return nullptr;
}

void Chunk::AddTagForCtx(
      const NluContext &nluContext,
      Chunk &chunk,
      SyntaxTag::Type::Val tag) {
  if (SyntaxTag::Type::kV == tag) {
    std::wstring word = chunk.GetStrFromSentence(nluContext.GetQuery());
    bool isZhu = Manager::Get().GetGkb().GetGkbVerb().IsZhu(word);
    if (isZhu) {
      chunk.AddTag(SyntaxTag::Type::kVw);
    }

    if (chunk.tags_.empty()) {
      auto segment = chunk.FindSeg_(nluContext, PosTag::Type::kV);
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
