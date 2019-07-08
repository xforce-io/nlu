#include "../segmentor.h"
#include "../conf/conf.h"
#include "../data/manager.h"
#include "../model/graph/graph.h"
#include "../model/graph/trigger/manager_triggers.h"
#include "ner/ner.h"
#include "basic/data/manager.h"
#include "basic/data/gkb/gkb.h"

namespace xforce { namespace nlu { namespace segmentor {

bool Segmentor::Init(
    const xforce::JsonType &confSeg,
    const xforce::JsonType &confNer) {
  bool ret = xforce::nlu::ner::Ner::Init(confNer);
  if (!ret) {
    return false;
  }

  ret = Conf::Get().Init(confSeg);
  if (!ret) {
    FATAL("fail_init_conf[segmentor]");
    return false;
  }

  ret = Manager::Get().Init();
  if (!ret) {
    FATAL("fail_init_data_manager[segmentor]");
    return false;
  }
  return true;
}

void Segmentor::Parse(
    const std::wstring &query, 
    std::shared_ptr<basic::NluContext> &nluContext) {
  auto graph = new Graph(query);
  graph->Process(nluContext->GetSegments(), nluContext->GetNameEntities());
  XFC_DELETE(graph)
}

void Segmentor::Tini() {
  ManagerTriggers::Tini();  
  Manager::Tini();  
  Conf::Tini();
}

}}}
