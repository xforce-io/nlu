#pragma once

#include "../../../public.h"
#include "storage_val.h"

namespace xforce { namespace nlu { namespace milkie {

class Frame;
class Sentence;
class StorageVal;
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
  inline std::shared_ptr<StorageVal> GetCurPattern() const;
  inline void StartMatch();
  inline void StartMatch(ssize_t offset);
  inline void StopMatch(bool succ);
  inline void StopMatch(bool succ, std::shared_ptr<StorageVal> storageItem);
  inline void SetStorage(
          const StorageKey &storageKey,
          StorageVal &storageItem);

  inline void SetStorageStr(
          const StorageKey &storageKey,
          const std::wstring &content,
          size_t offset);

  inline void RemoveStorage(
          const StorageKey &key);

  inline const std::shared_ptr<StorageVal> GetStorage(const StorageKey &key);
  inline const std::shared_ptr<StorageVal> GetStorage(const wchar_t *item);
  inline const std::wstring* GetStorageAsStr(const StorageKey &key);
  inline const std::wstring* GetStorageAsStr(const wchar_t *item);

  /*
   * mark : str env supported only now
   */
  inline void GetStorages(std::unordered_map<std::wstring, std::shared_ptr<StorageVal>> &kvs);

  inline void SetStoragePattern(StorageVal &storageItem);
  inline std::shared_ptr<StorageVal> GetStoragePattern();
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
#include "storage_val.h"

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

std::shared_ptr<StorageVal> Context::GetCurPattern() const {
  if (stack_.empty()) {
    return nullptr;
  }

  ssize_t topStartPos = stack_.top()->GetStartPos();
  return std::make_shared<StorageVal>(
      sentence_->GetSentence().substr(
        topStartPos, 
        curPos_ - topStartPos),
      topStartPos);
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

void Context::StopMatch(bool succ, std::shared_ptr<StorageVal> storageItem) {
  std::shared_ptr<Frame> framePoped = stack_.top();
  stack_.pop();
  if (succ) {
    stack_.top()->GetStorage().Merge(framePoped->GetStorage());
    if (storageItem != nullptr) {
      stack_.top()->SetStoragePattern(*storageItem);
    }
  } else {
    curPos_ = framePoped->GetStartPos();
  }
}

void Context::SetStorage(
        const StorageKey &storageKey,
        StorageVal &storageVal) {
  stack_.top()->GetStorage().Set(storageKey, storageVal);
}

void Context::SetStorageStr(
        const StorageKey &storageKey,
        const std::wstring &content,
        size_t offset) {
  stack_.top()->GetStorage().SetStr(storageKey, content, offset);
}

void Context::RemoveStorage(const StorageKey &storageKey) {
  stack_.top()->GetStorage().Remove(storageKey);
}

const std::shared_ptr<StorageVal> Context::GetStorage(const StorageKey &key) {
  std::shared_ptr<StorageVal> result;
  std::stack<std::shared_ptr<Frame>> tmpStack;
  while (!stack_.empty()) {
    auto frame = stack_.top();
    const std::shared_ptr<StorageVal> storageItem = frame->GetStorage().Get(key);
    if (storageItem != nullptr && result == nullptr) {
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

const std::shared_ptr<StorageVal> Context::GetStorage(const wchar_t *item) {
  return GetStorage(StorageKey(nullptr, item));
}

const std::wstring* Context::GetStorageAsStr(const StorageKey &key) {
  auto storageItem = GetStorage(key);
  if (nullptr != storageItem) {
    return storageItem->GetAsString();
  }
  return nullptr;
}

const std::wstring* Context::GetStorageAsStr(const wchar_t *item) {
  return GetStorageAsStr(StorageKey(nullptr, item));
}

void Context::GetStorages(std::unordered_map<std::wstring, std::shared_ptr<StorageVal>> &kvs) {
  kvs.clear();

  std::stack<std::shared_ptr<Frame>> tmpStack;
  while (!stack_.empty()) {
    auto frame = stack_.top();
    frame->GetStorage().Get(kvs);
    tmpStack.push(frame);
    stack_.pop();
  }

  while (!tmpStack.empty()) {
      stack_.push(tmpStack.top());
      tmpStack.pop();
  }
}

void Context::SetStoragePattern(StorageVal &storageItem) {
  stack_.top()->SetStoragePattern(storageItem);
}

std::shared_ptr<StorageVal> Context::GetStoragePattern() {
  if (stack_.top()->GetStoragePattern() != nullptr) {
    return stack_.top()->GetStoragePattern();
  } else {
    return GetCurPattern();
  }
}

bool Context::End() const {
  return curPos_ == (ssize_t)(sentence_->GetSentence().length());
}

size_t Context::Length() const {
  return sentence_->GetSentence().length();
}

}}}
