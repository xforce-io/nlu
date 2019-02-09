#include "../conf.h"

namespace xforce { namespace nlu { namespace milkie {

Conf *Conf::conf_ = new Conf();

Conf::Conf() {}

bool Conf::Init(const std::string &filepath) {
  const JsonType *jsonType = JsonType::CreateConf(filepath);
  if (nullptr == jsonType) {
    return false;
  }
  return Init(*jsonType);
}

bool Conf::Init(const xforce::JsonType &confJson) {
  std::string referFiledir;
  int ret;

  XFC_FAIL_HANDLE_FATAL(
      !confJson["debugMode"].IsStr(),
      "fail_get_debug_mode")
  debugMode_ = confJson["debugMode"].AsBool();

  XFC_FAIL_HANDLE_FATAL(
      !confJson["referFiledir"].IsStr(),
      "fail_get_refer_file_dir")
  referFiledir = confJson["referFiledir"].AsStr();

  ret = xforce::IOHelper::ScanFiles(referFiledir, referFilepaths_);
  XFC_FAIL_HANDLE_FATAL(
          ret <= 0,
          "file_scan_files_from_refer_filepath")

  return true;

  ERROR_HANDLE:
  return false;
}

void Conf::Tini() {
  XFC_DELETE(conf_)
}

}}}
