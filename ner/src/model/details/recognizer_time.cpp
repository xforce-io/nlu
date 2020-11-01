#include "../recognizer_timer.h"

namespace xforce { namespace nlu { namespace ner {

const std::wstring RecognizerTime::kNerTimeStoragePrefix = L"/nerTime"

RecognizerTime::RecognizerTime() :
    matcher_(new milkie::Matcher()) {}

RecognizerTime::~RecognizerTime() {
  XFC_DELETE(matcher_)
}

bool RecognizerTime::Init() {
  bool ret = matcher_->Init(Conf::Get().GetParserConfpath());
  if (!ret) {
    return false;
  }

  ret = matcher_->RegistSingle("time", kNerTimeStoragePrefix, RecognizerTime::MatcherCb_);
  if (!ret) {
    FATAL("fail_regist_time_matcher");
    return false;
  }
  return true;
}

void RecognizerTime::Process(std::shared_ptr<basic::NluContext> nluContext) {

}

static int MatcherCb_(
    const StorageKey &key, 
    const std::shared_ptr<StorageVal> &val,
    std::shared_ptr<basic::NluContext> nluContext);
  auto storageItems = val->Get();
  for (auto &storageItem : storageItems) {
  }

}}}
