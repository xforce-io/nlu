#pragma once

#include "../public.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext;

class Phrase {
 public:
  Phrase(
          size_t from,
          size_t to,
          std::shared_ptr<NluContext> nluContext);

  size_t GetFrom() const { return from_; }
  size_t GetTo() const { return to_; }
  std::shared_ptr<NluContext>& GetNluContext() { return nluContext_; }

 private:
  size_t from_;
  size_t to_;
  std::shared_ptr<NluContext> nluContext_;
};

}}}
