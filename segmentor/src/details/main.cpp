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

  Graph *graph = new xforce::nlu::Graph(L"张三、王二小、上官芳和李四参与了会议");
  graph->Process();
  graph->Profile();

  const std::vector<int> &offset = graph->GetOffsets();  
  std::wcout << "[" << offset.size() << std::endl;
  for (auto iter = offset.begin(); iter != offset.end(); ++iter) {
    std::wcout << *iter << std::endl;
  }

  XFC_DELETE(graph)

  Segmentor::Tini();  

  return 0;
}

#endif
