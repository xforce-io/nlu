#include "../syntax.h"
#include "../model/matcher.h"
#include "../conf/conf.h"

namespace xforce { namespace nlu { namespace syntax {

Syntax Syntax::syntax_;  

Syntax::Syntax() :
  matcher_(new Matcher()) {}

Syntax::~Syntax() {
  XFC_DELETE(matcher_)
}

bool Syntax::Init() {
  auto ret = matcher_->Init();
  if (!ret) {
    FATAL("fail_init_milkie");
    return false;
  }
  return true;
}

void Syntax::Process(basic::NluContext &nluContext) {
  matcher_->Match(nluContext);
}

bool Syntax::Init(const xforce::JsonType &confJson) {
  bool ret = Conf::Get().Init(confJson);
  if (!ret) {
    FATAL("fail_init_conf[syntax]");
    return false;
  }

  ret = syntax_.Init();
  if (!ret) {
    FATAL("fail_init_syntax");
    return false;
  }
  std::cout << "succ init pos" << std::endl;
  return true;
}

void Syntax::Parse(std::shared_ptr<basic::NluContext> nluContext) {
  return syntax_.Process(*nluContext);
}

}}}
