#include "../matcher.h"
#include "../../conf/conf.h"
#include "../../model/parser/parser.h"
#include "../../model/parser/parser_mid_conj.h"

namespace xforce { namespace nlu { namespace semantic {

Matcher::Matcher() :
        ruleEngine_(new milkie::Milkie()) {
  parsers_.push_back(new ParserMidConj());
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
  return true;
}

void Matcher::Match(std::shared_ptr<basic::NluContext> nluContext) {
  for (auto *parser : parsers_) {
    parser->Process(*nluContext);
  }
}

}}}
