#pragma once

#include "public.h"

namespace xforce { namespace nlu {

class NumericRecognizer {
 public: 
  inline static int ExtractArabicNumeral(
      const std::string &query,
      size_t offset); 
};

int NumericRecognizer::ExtractArabicNumeral(
    const std::string &query,
    size_t offset) {
  size_t i = offset;
  while (i < query.length() 
      && (
        (query[i] >= '0' && query[i] <= '9') 
        || '.' == query[i])) {
    ++i;
  }

  if (i-offset >= 2) {
    return i-offset;
  } else {
    return -1;
  }
}

}}
