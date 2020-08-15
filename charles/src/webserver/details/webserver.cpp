#include "../webserver.h"
#include "../../interface/interface.h"
#include "../../conf/conf.h"

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
      return;
    }

    if (!req.has_param("q")) {
      WebServer::SetErrnoAndReturn_(res, result, 3, "no q");
      return;
    }

    std::wstring query = *StrHelper::Str2Wstr(
            StrHelper::UrlDecode(
                    req.get_param_value("q")));
    auto nluContext = std::make_shared<basic::NluContext>(query);
    Interface::ParseRaw(flags, nluContext);

    WebServer::Dump_(nluContext, basic::Stage::kSegment, result);
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
