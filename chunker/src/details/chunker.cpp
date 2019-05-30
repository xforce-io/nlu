#include "../chunker.h"
#include "../model/matcher.h"

namespace xforce { namespace nlu { namespace chunker {

Chunker::Chunker() :
  matcher_(new Matcher()) {}

bool Chunker::Init(const xforce::JsonType &confJson) {
  auto ret = matcher_->Init();
  if (!ret) {
    FATAL("fail_init_milkie");
    return false;
  }
  return true;
}

void Chunker::Parse(
        const std::wstring &query,
        const basic::FragmentSet<basic::Segment> &segments,
        const basic::FragmentSet<basic::NameEntity> &nameEntities,
        basic::FragmentSet<basic::Chunk> &chunks) {
  for (size_t i=0; i < segments.Size(); ++i) {
    for (auto &posTag : segments[i]->GetPosTags()) {
      basic::PosTag::IsFuncWord(posTag)
    }
  }
}

void Chunker::Tini() {
}

}}}
