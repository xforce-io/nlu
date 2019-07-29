#include "../chunker.h"
#include "../model/matcher.h"
#include "../conf/conf.h"

namespace xforce { namespace nlu { namespace chunker {

Chunker Chunker::chunker_;

Chunker::Chunker() :
  matcher_(new Matcher()) {}

Chunker::~Chunker() {
  XFC_DELETE(matcher_)
}

bool Chunker::Init() {
  auto ret = matcher_->Init();
  if (!ret) {
    FATAL("fail_init_parser");
    return false;
  }
  return true;
}

void Chunker::Process(std::shared_ptr<basic::NluContext> nluContext) {
  matcher_->Match(nluContext);
}

bool Chunker::Init(const xforce::JsonType &confJson) {
  bool ret = Conf::Get().Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[chunker]");
    return false;
  }

  ret = chunker_.Init();
  if (!ret) {
    FATAL("fail_init_chunker");
    return false;
  }
  std::cout << "succ init chunker" << std::endl;
  return true;
}

void Chunker::Parse(std::shared_ptr<basic::NluContext> nluContext) {
  return chunker_.Process(nluContext);
}

}}}
