#pragma once

#include "../../../public.h"
#include "storage.h"

namespace xforce { namespace nlu { namespace milkie {

class Frame;
class Sentence;

class Context {
 public:
  inline Context(std::shared_ptr<basic::NluContext> nluContext);
  inline Context(const std::wstring &sentenceStr);
  virtual ~Context();

  inline void Reset();
  inline void Reset(const std::wstring &otherSentence);
  inline void Reset(size_t offset);
  const Sentence& GetSentence() const { return *sentence_; }
  Sentence& GetSentence() { return *sentence_; }
  inline void Pass(ssize_t n);
  inline void SetStartPos(ssize_t startPos);
  inline void SetCurPos(ssize_t curPos);
  ssize_t GetStartPos() const { return startPos_; }
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

  inline void Store();
  inline void Clear();

  inline const std::shared_ptr<StorageVal> GetCurStorage(const StorageKey &key);
  inline const std::shared_ptr<StorageVal> GetCurStorage(const wchar_t *item);
  inline const std::wstring* GetCurStorageAsStr(const StorageKey &key);
  inline const std::wstring* GetCurStorageAsStr(const wchar_t *item);
  inline const std::shared_ptr<StorageVal> GetStorage(const StorageKey &key);
  inline const std::wstring* GetStorageAsStr(const StorageKey &key);

  /*
   * mark : str env supported only now
   */
  const Storage& GetStorage() const { return storage_; }
  Storage& GetStorage() { return storage_; }

  inline void SetCurStoragePattern(StorageVal &storageItem);
  inline std::shared_ptr<StorageVal> GetCurStoragePattern();
  inline bool End() const;
  inline size_t Length() const;

 private:
  Sentence *sentence_;
  ssize_t startPos_;
  ssize_t curPos_;
  std::stack<std::shared_ptr<Frame>> stack_;

  Storage storage_;
};

}}}

#include "../sentence/sentence.h"
#include "frame.h"

namespace xforce { namespace nlu { namespace milkie {

Context::Context(std::shared_ptr<basic::NluContext> nluContext) :
    startPos_(0) {
  sentence_ = new Sentence(nluContext);
  Reset();
}

Context::Context(const std::wstring &sentenceStr) :
  Context(std::make_shared<basic::NluContext>(sentenceStr)) {}

void Context::Reset() {
  Reset(0);
}

void Context::Reset(const std::wstring &otherSentence) {
  sentence_ = new Sentence(otherSentence);
  Reset();
}

void Context::Reset(size_t offset) {
  curPos_ = offset;
  while (!stack_.empty()) {
    stack_.pop();
  }
  stack_.push(std::make_shared<Frame>(curPos_));
}

void Context::Pass(ssize_t n) {
  curPos_ += n;
}

void Context::SetStartPos(ssize_t startPos) {
  startPos_ = startPos;
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

void Context::Store() {
  std::stack<std::shared_ptr<Frame>> tmpStack;
  while (!stack_.empty()) {
    auto frame = stack_.top();
    frame->GetStorage().Store(storage_);
    tmpStack.push(frame);
    stack_.pop();
  }

  while (!tmpStack.empty()) {
      stack_.push(tmpStack.top());
      tmpStack.pop();
  }
}

void Context::Clear() {
  storage_.Clear();
}

const std::shared_ptr<StorageVal> Context::GetCurStorage(const StorageKey &key) {
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

const std::shared_ptr<StorageVal> Context::GetCurStorage(const wchar_t *item) {
  return GetCurStorage(StorageKey(nullptr, item));
}

const std::wstring* Context::GetCurStorageAsStr(const StorageKey &key) {
  auto storageItem = GetCurStorage(key);
  if (nullptr != storageItem) {
    return storageItem->GetAsString();
  }
  return nullptr;
}

const std::wstring* Context::GetCurStorageAsStr(const wchar_t *item) {
  return GetCurStorageAsStr(StorageKey(nullptr, item));
}

const std::shared_ptr<StorageVal> Context::GetStorage(const StorageKey &key) {
  return storage_.Get(key);
}

const std::wstring* Context::GetStorageAsStr(const StorageKey &key) {
  auto storageVal = GetStorage(key);
  if (nullptr != storageVal) {
    return storageVal->GetAsString();
  } else {
    return nullptr;
  }
}

void Context::SetCurStoragePattern(StorageVal &storageItem) {
  stack_.top()->SetStoragePattern(storageItem);
}

std::shared_ptr<StorageVal> Context::GetCurStoragePattern() {
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
