#include "../gkb_zk.h"

namespace xforce { namespace nlu { namespace basic {

bool GkbZk::Init(const std::string &filepath) {
  std::vector<std::string> lines;
  bool ret = IOHelper::ReadLinesFromFilepath(filepath, lines);
  if (!ret) {
    ERROR("fail_read_line_from[" << *StrHelper::Str2Wstr(filepath) << "]");
    return false;
  }

  for (auto &line : lines) {
    auto wline = StrHelper::Str2Wstr(line);

    std::vector<std::wstring> items;
    StrHelper::SplitStr(*wline, L'\t', items);
    if (items.size() < 2) {
      ERROR("invalid_gkb_line[" << wline << "]");
      continue;
    }

    auto posTag = PosTag::GetPosTag(items[1]);
    if (basic::PosTag::kUndef != posTag) {
      AddPosTag_(items[0], posTag);
    } else {
      if (items[1][0] < L'A' || items[1][0] > L'Z') {
        ERROR("invalid_gkb_line[" << wline << "]");
        continue;
      }
    }
  }
  return true;
}

void GkbZk::AddPosTag_(const std::wstring &key, PosTag::Type posTag) {
  BasicAddPosTag_(key, posTag);
  if (posTag == PosTag::kV) {
    BasicAddPosTag_(key, PosTag::kN);
  }
}

void GkbZk::BasicAddPosTag_(const std::wstring &key, PosTag::Type posTag) {
  auto iter = charToPos_.find(key);
  if (iter != charToPos_.end()) {
    iter->second->push_back(posTag);
  } else {
    auto val = std::make_shared<std::vector<PosTag::Type>>();
    val->push_back(posTag);
    charToPos_.insert(std::make_pair(key, val));
  }
}

}}}
