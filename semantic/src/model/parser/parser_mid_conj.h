#include "../../public.h"
#include "parser.h"

namespace xforce { namespace nlu { namespace semantic {

class ParserMidConj : public Parser {
 public:
  void Process(basic::NluContext &nluContext);
};

}}}