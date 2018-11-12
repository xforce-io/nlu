#include "../segmentor.h"
#include "../conf/conf.h"
#include "../data/manager.h"
#include "../model/graph/graph.h"
#include "../model/graph/trigger/manager_triggers.h"

namespace xforce { namespace nlu { namespace segmentor {

bool Segmentor::Init(const std::string &confpath) {
  setlocale(LC_ALL, "");

  bool ret = Conf::Get().Init(confpath);
  if (!ret) {
    FATAL("fail_init_conf_from[conf/segmentor.conf]");
    return false;
  }

  ret = Manager::Get().Init();
  if (!ret) {
    FATAL("fail_init_data_manager");
    return false;
  }
  return true;
}

void Segmentor::Parse(
    const std::wstring &query, 
    std::vector<size_t> offsets) {
  Graph *graph = new Graph(query);
  graph->Process();
  offsets.assign(graph->GetOffsets().begin(), graph->GetOffsets().end());
  XFC_DELETE(graph)
}

void Segmentor::Tini() {
  ManagerTriggers::Tini();  
  Manager::Tini();  
}

}}}
