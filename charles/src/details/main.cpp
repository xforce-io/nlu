#include "../public.h"
#include "../model/runtime.h"
#include "../model/base_modules.h"
#include "../charles.h"
#include "../webserver/webserver.h"

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

  if (!Charles::Init(*conf)) {
    FATAL("fail_init_charles");
    return 2;
  }

  WebServer webServer;
  if (!webServer.Init()) {
    FATAL("fail_init_webserver");
    return 3;
  }
  return 0;
}

#endif
