#include "../model/graph/graph.h"
#include "../model/graph/trigger/manager_triggers.h"
#include "../conf/conf.h"
#include "../public/req_tracer.h"

#ifndef UT_TEST

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce;
using namespace xforce::nlu;

int main() {
  LOGGER_SYS_INIT("conf/log.conf")

  setlocale(LC_ALL, "");

  bool ret = Conf::Get().Init("conf/segmentor.conf");
  if (!ret) {
    FATAL("fail_init_conf_from[conf/segmentor.conf]");
    return -1;
  }

  ret = Manager::Get().Init();
  if (!ret) {
    FATAL("fail_init_data_manager");
    return -2;
  }

  Graph *graph = new xforce::nlu::Graph("这样其实还好");
  graph->Process();
  graph->Profile();
  XFC_DELETE(graph)

  ManagerTriggers::Tini();  
  Manager::Tini();  
  return 0;
}

#endif
