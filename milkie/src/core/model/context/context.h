#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace milkie {

class Frame;
class Sentence;
class StorageItem;

class Context {
 public:
  Context(
      std::shared_ptr<basic::NluContext> nluContext,
      ssize_t curPos,
      std::stack<std::shared_ptr<Frame>> stack);
  virtual ~Context();

  inline void Reset();
  inline void Reset(const std::wstring &otherSentence);
  const Sentence& GetSentence() const { return *sentence_; }
  Sentence& GetSentence() { return *sentence_; }
  void Pass(ssize_t n);
  void SetCurPos(ssize_t curPos);
  ssize_t GetCurPos() const { return curPos_; }
  inline std::shared_ptr<std::wstring> GetCurPattern() const;
  inline void StartMatch();
  inline void StartMatch(ssize_t offset);
  inline void StopMatch(bool succ);
  inline void StopMatch(bool succ, StorageItem *storageItem);
  inline void SetStorage(const std::wstring *key, StorageItem &storageItem);
  inline void SetStorageStr(const std::wstring *key, const std::wstring &value);
  inline void RemoveStorage(const std::wstring *key);
  inline const StorageItem* GetStorage(const std::wstring &key);
  inline const Wstrings* GetStorageAsItems(const std::wstring &key);
  inline const std::wstring* GetStorageAsStr(const std::wstring &key);
  inline void SetStoragePattern(StorageItem &storageItem);
  inline StorageItem* GetStoragePattern();
  inline bool End() const;
  inline size_t Length() const;
  inline Context* Copy();

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

Context::Context(
    std::shared_ptr<basic::NluContext> nluContext,
    ssize_t curPos,
    std::stack<std::shared_ptr<Frame>> stack) {
  sentence_ = new Sentence(nluContext);
}

Context::~Context() {
  XFC_DELETE(sentence_)
}

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
    stack_.top()->CopyStorage(*framePoped);
    if (nullptr != storageItem) {
      stack_.top()->SetStoragePattern(*storageItem);
    }
  } else {
    curPos_ = framePoped->GetStartPos();
  }
}

void Context::SetStorage(const std::wstring *key, StorageItem &storageItem) {
  if (nullptr != key) {
    stack_.top()->SetStorage(*key, storageItem);
  }
}

void Context::SetStorageStr(const std::wstring *key, const std::wstring &value) {
  if (nullptr != key) {
    stack_.top()->SetStorageStr(*key, value);
  }
}

void Context::RemoveStorage(const std::wstring *key) {
  stack_.top()->RemoveStorage(*key);
}

const StorageItem* Context::GetStorage(const std::wstring &key) {
  std::stack<std::shared_ptr<Frame>> tmpStack;
  while (!stack_.empty()) {
    auto frame = stack_.top();
    const StorageItem* storageItem = frame->GetStorage(key);
    if (nullptr != storageItem) {
      return storageItem;
    }
    tmpStack.push(frame);
  }

  while (!tmpStack.empty()) {
      stack_.push(tmpStack.top());
  }
  return nullptr;
}

const Wstrings* Context::GetStorageAsItems(const std::wstring &key) {
  auto storageItem = GetStorage(key);
  if (nullptr != storageItem) {
    return &(storageItem->Get());
  }
  return nullptr;
}

const std::wstring* Context::GetStorageAsStr(const std::wstring &key) {
  auto storageItem = GetStorage(key);
  if (nullptr != storageItem) {
    return storageItem->GetAsString();
  }
  return nullptr;
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
  return curPos_ == sentence_->GetSentence().length();
}

size_t Context::Length() const {
  return sentence_->GetSentence().length();
}

Context* Context::Copy() {
  return new Context(sentence_->GetNluContext(), curPos_, stack_);
}

}}}
