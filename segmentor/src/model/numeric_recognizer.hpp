#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace segmentor {

class NumericRecognizer {
 public: 
  inline static int ExtractArabicNumeral(
      const std::wstring &query,
      size_t offset); 
};

int NumericRecognizer::ExtractArabicNumeral(
    const std::wstring &query,
    size_t offset) {
  size_t i = offset;
  while (i < query.length() 
      && (
        (query[i] >= L'0' && query[i] <= L'9') 
        || '.' == query[i])) {
    ++i;
  }

  if (i-offset >= 2) {
    return i-offset;
  } else {
    return -1;
  }
}

}}}
