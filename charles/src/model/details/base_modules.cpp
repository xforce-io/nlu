#include "../base_modules.h"

#include "basic/basic.h"
#include "segmentor/segmentor.h"
#include "pos_tagging/pos_tagging.h"
#include "chunker/chunker.h"
#include "syntax/syntax.h"
#include "semantic/semantic.h"

namespace xforce { namespace nlu { namespace charles {

bool BaseModules::Init(const xforce::JsonType &conf) {
  bool ret = xforce::nlu::basic::Basic::Init(conf["basic"]);
  if (!ret) {
    FATAL("fail_init_basic");
    return false;
  }

  ret = xforce::nlu::segmentor::Segmentor::Init(conf["segmentor"], conf["ner"]);
  if (!ret) {
    FATAL("fail_init_segmentor");
    return false;
  }

  ret = xforce::nlu::pos::PosTagging::Init(conf["pos"]);
  if (!ret) {
    FATAL("fail_init_pos_tagging");
    return false;
  }

  ret = xforce::nlu::chunker::Chunker::Init(conf["chunker"]);
  if (!ret) {
    FATAL("fail_init_chunker");
    return false;
  }

  ret = xforce::nlu::syntax::Syntax::Init(conf["syntax"]);
  if (!ret) {
    FATAL("fail_init_syntax");
    return false;
  }

  ret = xforce::nlu::semantic::Semantic::Init(conf["semantic"]);
  if (!ret) {
    FATAL("fail_init_semantic");
    return false;
  }
  return true;
}

}}}
