#include "../model/graph/graph.h"
#include "../model/graph/trigger/manager_triggers.h"
#include "../conf/conf.h"
#include "../public/req_tracer.h"
#include "../segmentor.h"

#ifndef UT_TEST

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce;
using namespace xforce::nlu;

int main() {
  LOGGER_SYS_INIT("conf/log.conf")

  bool ret = Segmentor::Init("conf/segmentor.conf");  
  if (!ret) {
    return -1;
  }

  Graph *graph = new xforce::nlu::Graph("这样其实还好");
  graph->Process();
  graph->Profile();
  XFC_DELETE(graph)

  Segmentor::Tini();  

  return 0;
}

#endif
