#include "../matcher.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace syntax {

const std::wstring Matcher::kChunkStoragePrefix = L"chunkSep";
const std::wstring Matcher::kSyntacticStoragePrefix = L"syntactic";

Matcher::Matcher() :
    milkie_(new milkie::Milkie()) {}

bool Matcher::Init() {
  bool ret = milkie_->Init(Conf::Get().GetMilkieConfpath());
  if (!ret) {
    FATAL("fail_init[milkie]");
    return false;
  }

  featureExtractor_ = milkie_->GetManager().GetFeatureExtractor(L"syntax");
  if (featureExtractor_ == nullptr) {
    FATAL("fail_get_feature_extractor_named_syntax");
    return false;
  }
  return true;
}

void Matcher::Match(basic::NluContext &nluContext) {
  auto cur = nluContext.GetChunkSeps().Begin();
  while (cur != nluContext.GetChunkSeps().End()) {
    auto next = cur;
    ++next;

    if (next != nluContext.GetChunkSeps().End()) {
      auto fragment = basic::NluContext::Build(
              (*cur)->GetOffset(),
              (*next)->GetOffset());
    } else {
      auto fragment = basic::NluContext::Build(
              (*cur)->GetOffset(),
              nluContext.GetQuery().length());
    }


  }
}

Matcher::~Matcher() {
  XFC_DELETE(milkie_)
}

}}}
