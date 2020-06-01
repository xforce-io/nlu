#include "../semantic.h"
#include "../conf/conf.h"
#include "../model/matcher.h"

namespace xforce { namespace nlu { namespace semantic {

Semantic Semantic::semantic_;

Semantic::Semantic() :
  matcher_(new Matcher()) {}

Semantic::~Semantic() {
  XFC_DELETE(matcher_)
}

bool Semantic::Init() {
  auto ret = matcher_->Init();
  if (!ret) {
    FATAL("fail_init_milkie");
    return false;
  }
  return true;
}

void Semantic::Process(std::shared_ptr<basic::NluContext> nluContext) {
  matcher_->Match(nluContext);
}

bool Semantic::Init(const xforce::JsonType &confJson) {
  bool ret = Conf::Get().Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[semantic]");
    return false;
  }

  ret = semantic_.Init();
  if (!ret) {
    FATAL("fail_init_semantic");
    return false;
  }
  std::cout << "succ init pos" << std::endl;
  return true;
}

void Semantic::Parse(std::shared_ptr<basic::NluContext> nluContext) {
  return semantic_.Process(nluContext);
}

}}}
