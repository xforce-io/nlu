#include "../public.h"
#include "../model/runtime.h"
#include "../model/base_modules.h"

#ifndef UT_TEST

LOGGER_IMPL(xforce::xforce_logger, L"charles")

using namespace xforce;
using namespace xforce::nlu;
using namespace xforce::nlu::charles;

int main() {
  setlocale(LC_ALL, "");

  LOGGER_SYS_INIT(L"conf/log.conf")

  const xforce::JsonType* conf = xforce::JsonType::CreateConf("conf/charles.conf");
  if (NULL == conf) {
    FATAL("fail_parse_conf[charles.conf]");
    return 1;
  }

  bool ret = BaseModules::Get().Init(*conf);
  if (!ret) {
    FATAL("fail_init_base_module");
    return 2;
  }

  ret = nlu::basic::Manager::Get().Init();
  if (!ret) {
    FATAL("fail_init_data_manager");
    return 3;
  }

  Runtime *runtime = new Runtime();  
  ret = runtime->Process(L"周杰伦、刘亦菲和王凯的关系很好");
  if (!ret) {
    return 4;
  }

  JsonType jsonType;
  runtime->DumpAnalysisContext(jsonType);
  std::stringstream ss;
  jsonType.DumpJson(ss);
  std::cout << ss.str() << std::endl;
  return 0;
}

#endif
