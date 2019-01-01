#pragma once

#include "dep.h"
#include "aho_corasick.hpp"

namespace xforce { namespace nlu { namespace milkie {

typedef std::vector<std::wstring> Wstrings;

class Helper {
 public: 
  std::wstring PreprocessExprLine(const std::wstring &line); 
};

}}}
