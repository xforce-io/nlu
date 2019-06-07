#include "../chunker.h"
#include "../model/matcher.h"

namespace xforce { namespace nlu { namespace chunker {

Matcher *Chunker::matcher_ = new Matcher();

bool Chunker::Init(const xforce::JsonType &confJson) {
  auto ret = matcher_->Init();
  if (!ret) {
    FATAL("fail_init_milkie");
    return false;
  }
  return true;
}

void Chunker::Parse(basic::NluContext &nluContext) {
  matcher_->Match(nluContext);
}

void Chunker::Tini() {
  XFC_DELETE(matcher_)
}

}}}
