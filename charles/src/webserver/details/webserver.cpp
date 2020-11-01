#include "../webserver.h"
#include "../../interface/interface.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace charles {

bool WebServer::Init() {
  server_.Post("/raw", [&](const Request& req, Response& res) {
      JsonType result;
      auto body = req.body;
      auto json = std::shared_ptr<const JsonType>(JsonType::ParseJson(body.c_str()));
      if (nullptr == json) {
        WebServer::SetErrnoAndReturn_(res, result, 1, "invalid json(bad json)");
        WARN("bad_json[" << *StrHelper::Str2Wstr(body) << "]");
        return;
      }

      auto &flagsJson = (*json)["flags"];
      if (!flagsJson.IsStr()) {
        WebServer::SetErrnoAndReturn_(res, result, 1, "invalid json(invalid flags)");
        return;
      }

      std::vector<std::string> flags;
      StrHelper::SplitStr(flagsJson.AsStr(), ',', flags);
      if (flags.empty()) {
        WebServer::SetErrnoAndReturn_(res, result, 2, "flag error(empty flags)");
        return;
      }

      auto &queries = (*json)["queries"];
      if (!queries.IsList()) {
        WebServer::SetErrnoAndReturn_(res, result, 1, "invalid json(invalid queries)");
        return;
      }

      for (size_t i=0; i < queries.Size(); ++i) {
        if (!queries[i].IsStr()) {
          WebServer::SetErrnoAndReturn_(res, result, 1, "invalid json(invalid str)");
          return;
        }

        std::wstring query = *StrHelper::Str2Wstr(queries[i].AsStr());
        auto nluContext = std::make_shared<basic::NluContext>(query);
        Interface::ParseRaw(flags, nluContext);
        for (auto &flag : flags) {
          if (flag == "segment") {
            WebServer::Dump_(nluContext, basic::Stage::kSegment, result[i]);
          }
        }
      }

      std::stringstream resContent;
      result.DumpJson(resContent);
      res.set_content(resContent.str(), "text/plain");
  });

  std::cout << "start listening ..." << std::endl;

  server_.listen(
      Conf::Get().GetHost().c_str(), 
      Conf::Get().GetPort());
  return true;
}


void WebServer::Dump_(
    std::shared_ptr<basic::NluContext> &nluContext,
    basic::Stage::Val stage,
    JsonType &result) {
  if (basic::Stage::kSegment == stage) {
    size_t cnt = 0;
    for (auto &fragment : nluContext->Get<basic::Segment>().GetAll()) {
      result["segment"][cnt]["word"] = nluContext->GetQuery().substr(fragment->GetOffset(), fragment->GetLen());
      ++cnt;
    }
  }
}


}}}
