#include "../model/graph/graph.h"
#include "../model/graph/trigger/manager_triggers.h"
#include "../conf/conf.h"
#include "../segmentor.h"

#ifndef UT_TEST

LOGGER_IMPL(xforce::xforce_logger, "segmentor")

using namespace xforce;
using namespace xforce::nlu::segmentor;

int main() {
  LOGGER_SYS_INIT("conf/log.conf")

  bool ret = Segmentor::Init("conf/segmentor.conf");  
  if (!ret) {
    return -1;
  }

  Timer timer;

  Graph *graph = new Graph(L"但是奇怪的是，刘亦菲的侧面有时候角度不一样，拍出来的感觉也不一样，像有的杂志封面上，刘亦菲的侧面就显得没有那么惊艳了，估计是左右脸的缘故吧！");
  Graph::Offsets offsets;
  Graph::NameEntities nameEntities;

  timer.Start(true);
  graph->Profile(offsets, nameEntities);
  timer.Stop(true);

  for (xforce::nlu::ner::NameEntity* nameEntity : nameEntities) {
    XFC_DELETE(nameEntity)
  }

  std::wcout << "cost[" << timer.TimeUs() << "]" << std::endl; 

  XFC_DELETE(graph)

  Segmentor::Tini();  
  return 0;
}

#endif
