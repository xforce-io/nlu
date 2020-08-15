#pragma once

#include "../public.h"

using namespace httplib;

namespace xforce { namespace nlu { namespace charles {

class WebServer {
 public:
  bool Init();

 private:
  void ParseRaw_(
      const std::wstring &query,
      const std::vector<std::string> flags);

  static void Dump_(
          std::shared_ptr<basic::NluContext> &nluContext,
          basic::Stage::Val stage,
          JsonType &result);

  inline static void SetErrnoAndReturn_(
          Response &res,
          JsonType &resultJson,
          int errNo,
          const std::string &errmsg);

private:
  Server server_;
};

void WebServer::SetErrnoAndReturn_(
    Response &res,
    JsonType &resultJson,
    int errNo,
    const std::string &errmsg) {
  resultJson["errno"] = errno;
  resultJson["errmsg"] = errmsg;

  std::stringstream resContent;
  resultJson.DumpJson(resContent);
  res.set_content(resContent.str(), "text/plain");
}

}}}