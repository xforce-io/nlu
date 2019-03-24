#include "../chunker.h"
#include "../conf/conf.h"

namespace xforce { namespace nlu { namespace chunker {

bool Chunker::Init(const xforce::JsonType &confJson) {
  bool ret = Conf::Get().Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[ner]");
    return false;
  }

  ret = milkie::Milkie::Init("conf/milkie.conf");
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
    auto &segment = segments[i];
    auto syntaxTag = basic::SyntaxTag::GetSyntaxTag(segment->GetPosCtbTag());
    if (syntaxTag != basic::SyntaxTag::kUndef) {
      chunks.Add(basic::Chunk(syntaxTag, segment->GetOffset(), segment->GetLen()));
    }
  }
}

void Chunker::Tini() {
  Conf::Tini();
}

}}}
