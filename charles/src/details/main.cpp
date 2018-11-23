#include "../public.h"

#ifndef UT_TEST

LOGGER_IMPL(xforce::xforce_logger, "charles")

using namespace xforce;

int main() {
  LOGGER_SYS_INIT("conf/log.conf")
  return 0;
}

#endif
