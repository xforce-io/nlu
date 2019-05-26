#pragma once

#include "../../../public.h"
#include "../entry/entry.h"

namespace xforce { namespace nlu { namespace basic {

template <class EntryType>
class Table {
 public:
  Table() {}
  virtual ~Table();

  bool Init(const std::string &filepath);
  inline const std::vector<EntryType*>* GetEntries(const std::wstring &word) const;

 private:
  void PutIntoInverted_(EntryType &entry);

 private:
  std::list<EntryType*> entries_;
  std::unordered_map<std::wstring, std::vector<EntryType*>> inverted_;
};

template <class EntryType>
Table<EntryType>::~Table() {
  for (auto *entry : entries_) {
    delete entry;
  }
}

template <class EntryType>
bool Table<EntryType>::Init(const std::string &filepath) {
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
      return false;
    }

    auto *entryType = new EntryType();
    if (!entryType->Parse(items)) {
      ERROR("fail_parse_items[" << wline << "]");
      return false;
    }
    entries_.push_back(entryType);
    PutIntoInverted_(entryType);
  }
  return true;
}

template <class EntryType>
const std::vector<EntryType*>* Table<EntryType>::GetEntries(const std::wstring &word) const {
  auto iter = inverted_.find(word);
  if (iter != inverted_.end()) {
    return &iter->second;
  } else {
    return nullptr;
  }
}

template <class EntryType>
void Table<EntryType>::PutIntoInverted_(EntryType &entry) {
  auto iter = inverted_.find(entry.GetWord());
  if (iter != inverted_.end()) {
    iter->second.push_back(&entry);
  } else {
    std::vector<EntryType*> entries;
    entries.push_back(&entry);
    inverted_.insert(std::make_pair(entry.GetWord(), entries));
  }
}

}}}
