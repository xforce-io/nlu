#include "../matcher.h"

namespace xforce { namespace nlu { namespace chunker {

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init("conf/milkie.conf");
  if (!ret) {
    FATAL("fail_init[milkie]");
    return false;
  }

  featureExtractor_ = milkie_->GetManager().GetFeatureExtractor(L"chunker");
  if (featureExtractor_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_chunker");
    return false;
  }
  return true;
}

void Matcher::Match(const std::wstring &query) {
  auto context = std::make_shared<milkie::Context>(query);
  auto errCode = featureExtractor_->MatchPattern(*context);
  if (milkie::Errno::kOk != errCode) {
    return;
  }

  milkie::StorageKey storageKey(nullptr, L"modifier");
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

}}}
