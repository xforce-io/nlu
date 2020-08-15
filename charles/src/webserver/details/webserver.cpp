#include "../webserver.h"
#include "../../interface/interface.h"

namespace xforce { namespace nlu { namespace charles {

bool WebServer::Init() {
  server_.Get("/raw", [](const Request& req, Response& res) {
    JsonType result;
    std::vector<std::string> flags;
    if (req.has_param("flags")) {
      auto val = req.get_param_value("flags");
      StrHelper::SplitStr(val, ',', flags);
      if (flags.empty()) {
        WebServer::SetErrnoAndReturn_(res, result, 1, "flag error");
        return;
      }
    } else {
      WebServer::SetErrnoAndReturn_(res, result, 1, "flag error");
    }

    if (!req.has_header("q")) {
      WebServer::SetErrnoAndReturn_(res, result, 3, "no q");
      return;
    }

    std::wstring query = *StrHelper::Str2Wstr(req.get_param_value("q"));
    auto nluContext = std::make_shared<basic::NluContext>(query);
    Interface::ParseRaw(flags, nluContext);

    WebServer::Dump_(nluContext, basic::Stage::kSegment, result);
    std::stringstream resContent;
    result.DumpJson(resContent);
    res.set_content(resContent.str(), "text/plain");
  });
  server_.listen("localhost", 1234);
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