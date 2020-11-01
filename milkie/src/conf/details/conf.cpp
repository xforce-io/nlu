#include "../conf.h"

namespace xforce { namespace nlu { namespace milkie {

Conf::Conf() {}

bool Conf::Init(const std::string &filepath) {
  const JsonType *jsonType = JsonType::CreateConf(filepath);
  if (nullptr == jsonType) {
    FATAL("fail_create_json_from_confpath");
    return false;
  }
  return Init(*jsonType);
}

bool Conf::Init(const xforce::JsonType &confJson) {
  std::string exprFiledir;
  std::string referFiledir;
  std::string codeSegFiledir;

  XFC_FAIL_HANDLE_FATAL(
      !confJson["exprFiledir"].IsStr(),
      "fail_get_expr_file_dir")
  exprFiledir = confJson["exprFiledir"].AsStr();

  xforce::IOHelper::ScanFiles(exprFiledir, exprFilepaths_);

  XFC_FAIL_HANDLE_FATAL(
      !confJson["referFiledir"].IsStr(),
      "fail_get_refer_file_dir")
  referFiledir = confJson["referFiledir"].AsStr();

  XFC_FAIL_HANDLE_FATAL(
      !confJson["codeSegLuaFiledir"].IsStr(),
      "fail_get_code_seg_lua_file_dir")
  codeSegFiledir = confJson["codeSegLuaFiledir"].AsStr();

  xforce::IOHelper::ScanFiles(referFiledir, referFilepaths_);
  xforce::IOHelper::ScanFiles(codeSegFiledir, codeSegFilepaths_);
  return true;

  ERROR_HANDLE:
  return false;
}

}}}
