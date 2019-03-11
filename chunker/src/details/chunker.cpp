#include "../chunker.h"
#include "../conf/conf.h"

namespace xforce { namespace nlu { namespace chunker {

bool Chunker::Init(const xforce::JsonType &confJson) {
  bool ret = Conf::Get().Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[ner]");
    return false;
  }
  return true;
}

void Chunker::Parse(
        const std::wstring &query,
        basic::FragmentSet<basic::Segment> &segments,
        basic::FragmentSet<basic::NameEntity> &nameEntities) {

}

void Chunker::Tini() {
  Conf::Tini();
}

}}}
