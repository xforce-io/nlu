#include "../gkb_zk.h"

namespace xforce { namespace nlu { namespace basic {

bool GkbZk::Init(const std::string &filepath) {
  std::vector<std::string> lines;
  bool ret = IOHelper::ReadLinesFromFilepath(filepath, lines);
  if (!ret) {
    ERROR("fail_read_line_from[" << filepath << "]");
    return false;
  }

  for (auto &line : lines) {
    auto wline = StrHelper::Str2Wstr(line);

    std::vector<std::wstring> items;
    StrHelper::SplitStr(*wline, L'\t', items);
  }
  return true;
}

GkbZk::~GkbZk() {

}

}}}
