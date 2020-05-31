#include "../../public.h"
#include "parser.h"

namespace xforce { namespace nlu { namespace semantic {

class ParserMidConj : public Parser {
 protected:
  bool Filter_(basic::NluContext &nluContext);
  void Process_(basic::NluContext &nluContext);

 private:
  template <typename FragmentType>
  bool ProcessFeature_(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> &conj);

 private:
  std::vector<std::shared_ptr<basic::Segment>> conjs_;
};

}}}