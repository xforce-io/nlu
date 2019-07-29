#pragma once

namespace xforce { namespace nlu { namespace milkie {

struct Errno {
    enum Code {
      kOk,
      kFiltered,
      kNotMatched,
      kOther,
    };
};

}}}
