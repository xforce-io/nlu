#include "../matcher.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace semantic {

Matcher::Matcher() :
        ruleEngine_(new milkie::Milkie()) {
}

Matcher::~Matcher() {
  for (auto *parser : parsers_) {
    XFC_DELETE(parser);
  }
  XFC_DELETE(ruleEngine_)
}

bool Matcher::Init() {
  bool ret = ruleEngine_->Init(Conf::Get().GetParserConfpath());
  if (!ret) {
    FATAL("fail_init_semantic[parser]");
    return false;
  }
}

void Matcher::Matcher(std::shared_ptr<basic::NluContext> nluContext) {

}

}}}