#pragma once

#include "../../../public.h"

namespace xforce { namespace nlu { namespace milkie {

class Frame;
class Sentence;
class StorageItem;
class StorageKey;

class Context {
 public:
  inline Context(std::shared_ptr<basic::NluContext> nluContext);
  inline Context(const std::wstring &sentenceStr);
  virtual ~Context();

  inline void Reset();
  inline void Reset(const std::wstring &otherSentence);
  const Sentence& GetSentence() const { return *sentence_; }
  Sentence& GetSentence() { return *sentence_; }
  inline void Pass(ssize_t n);
  inline void SetCurPos(ssize_t curPos);
  ssize_t GetCurPos() const { return curPos_; }
  inline std::shared_ptr<std::wstring> GetCurPattern() const;
  inline void StartMatch();
  inline void StartMatch(ssize_t offset);
  inline void StopMatch(bool succ);
  inline void StopMatch(bool succ, StorageItem *storageItem);
  inline void SetStorage(
          const StorageKey &storageKey,
          StorageItem &storageItem);

  inline void SetStorageStr(
          const StorageKey &storageKey,
          const std::wstring &value);

  inline void RemoveStorage(
          const StorageKey &key);

  inline const StorageItem* GetStorage(const StorageKey &key);
  inline const StorageItem* GetStorage(const wchar_t *item);
  inline const Wstrings* GetStorageAsItems(const StorageKey &key);
  inline const std::wstring* GetStorageAsStr(const StorageKey &key);
  inline const std::wstring* GetStorageAsStr(const wchar_t *item);

  /*
   * mark : str env supported only now
   */
  inline void GetStorages(std::unordered_map<std::wstring, std::wstring> &kvs);

  inline void SetStoragePattern(StorageItem &storageItem);
  inline StorageItem* GetStoragePattern();
  inline bool End() const;
  inline size_t Length() const;

 private:
  Sentence *sentence_;
  ssize_t curPos_;
  std::stack<std::shared_ptr<Frame>> stack_;
};

}}}

#include "../sentence/sentence.h"
#include "frame.h"
#include "storage_item.h"

namespace xforce { namespace nlu { namespace milkie {

Context::Context(std::shared_ptr<basic::NluContext> nluContext) {
  sentence_ = new Sentence(nluContext);
  Reset();
}

Context::Context(const std::wstring &sentenceStr) :
  Context(std::make_shared<basic::NluContext>(sentenceStr)) {}

void Context::Reset() {
  curPos_ = 0;  
  while (!stack_.empty()) {
    stack_.pop();
  }
  stack_.push(std::make_shared<Frame>(curPos_));
}

void Context::Reset(const std::wstring &otherSentence) {
  sentence_ = new Sentence(otherSentence);
  Reset();
}

void Context::Pass(ssize_t n) {
  curPos_ += n;
}

void Context::SetCurPos(ssize_t curPos) {
  curPos_ = curPos;
}

std::shared_ptr<std::wstring> Context::GetCurPattern() const {
  if (stack_.empty()) {
    return nullptr;
  }

  ssize_t topStartPos = stack_.top()->GetStartPos();
  return std::make_shared<std::wstring>(
      sentence_->GetSentence().substr(
        topStartPos, 
        curPos_ - topStartPos));
}

void Context::StartMatch() {
  stack_.push(std::make_shared<Frame>(curPos_));
}

void Context::StartMatch(ssize_t offset) {
  stack_.push(std::make_shared<Frame>(curPos_));
  curPos_ = offset;
}

void Context::StopMatch(bool succ) {
  StopMatch(succ, nullptr);
}

void Context::StopMatch(bool succ, StorageItem *storageItem) {
  std::shared_ptr<Frame> framePoped = stack_.top();
  stack_.pop();
  if (succ) {
    stack_.top()->GetStorage().Merge(framePoped->GetStorage());
    if (nullptr != storageItem) {
      stack_.top()->SetStoragePattern(*storageItem);
    }
  } else {
    curPos_ = framePoped->GetStartPos();
  }
}

void Context::SetStorage(
        const StorageKey &storageKey,
        StorageItem &storageItem) {
  stack_.top()->GetStorage().Set(storageKey, storageItem);
}

void Context::SetStorageStr(
        const StorageKey &storageKey,
        const std::wstring &value) {
  stack_.top()->GetStorage().SetStr(storageKey, value);
}

void Context::RemoveStorage(const StorageKey &storageKey) {
  stack_.top()->GetStorage().Remove(storageKey);
}

const StorageItem* Context::GetStorage(const StorageKey &key) {
  const StorageItem *result = nullptr;
  std::stack<std::shared_ptr<Frame>> tmpStack;
  while (!stack_.empty()) {
    auto frame = stack_.top();
    const StorageItem* storageItem = frame->GetStorage().Get(key);
    if (nullptr != storageItem && nullptr == result) {
      result = storageItem;
    }
    tmpStack.push(frame);
    stack_.pop();
  }

  while (!tmpStack.empty()) {
      stack_.push(tmpStack.top());
      tmpStack.pop();
  }
  return result;
}

const StorageItem* Context::GetStorage(const wchar_t *item) {
  return GetStorage(*new StorageKey(nullptr, item));
}

const Wstrings* Context::GetStorageAsItems(const StorageKey &key) {
  auto storageItem = GetStorage(key);
  if (nullptr != storageItem) {
    return &(storageItem->Get());
  }
  return nullptr;
}

const std::wstring* Context::GetStorageAsStr(const StorageKey &key) {
  auto storageItem = GetStorage(key);
  if (nullptr != storageItem) {
    return storageItem->GetAsString();
  }
  return nullptr;
}

const std::wstring* Context::GetStorageAsStr(const wchar_t *item) {
  return GetStorageAsStr(*new StorageKey(nullptr, item));
}

void Context::GetStorages(std::unordered_map<std::wstring, std::wstring> &kvs) {
  kvs.clear();

  std::stack<std::shared_ptr<Frame>> tmpStack;
  while (!stack_.empty()) {
    auto frame = stack_.top();
    frame->GetStorage().GetStrs(kvs);
    tmpStack.push(frame);
    stack_.pop();
  }

  while (!tmpStack.empty()) {
      stack_.push(tmpStack.top());
      tmpStack.pop();
  }
}

void Context::SetStoragePattern(StorageItem &storageItem) {
  stack_.top()->SetStoragePattern(storageItem);
}

StorageItem* Context::GetStoragePattern() {
  if (nullptr != stack_.top()->GetStoragePattern()) {
    return stack_.top()->GetStoragePattern();
  } else {
    return new StorageItem(&*GetCurPattern());
  }
}

bool Context::End() const {
  return curPos_ == (ssize_t)(sentence_->GetSentence().length());
}

size_t Context::Length() const {
  return sentence_->GetSentence().length();
}

}}}
