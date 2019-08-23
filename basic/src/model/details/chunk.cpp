#include "../chunk.h"
#include "../../data/manager.h"
#include "../../data/gkb/gkb.h"
#include "../nlu_context.h"

namespace xforce { namespace nlu { namespace basic {

const std::string& Chunk::GetCategory() const {
  static const std::string kCategory = "chunk";
  return kCategory;
}

void Chunk::Dump(JsonType &jsonType) {
  Super::Dump(jsonType);
  for (auto &syntaxTag : tags_) {
    jsonType["syn"].Append(*(StrHelper::Wstr2Str(SyntaxTag::Str(syntaxTag))));
  }
}

void Chunk::AddTagForCtx(
      const NluContext &nluContext,
      Chunk &chunk,
      SyntaxTag::Type::Val tag) {
  if (SyntaxTag::Type::kV == tag) {
    std::wstring word = chunk.GetStrFromSentence(nluContext.GetQuery());
    bool isZhu = Manager::Get().GetGkb().GetGkbVerb().isZhu(word);
    if (isZhu) {
      chunk.AddTag(SyntaxTag::Type::kVw);
    }
    chunk.AddTag(tag);
  }
}

}}}
