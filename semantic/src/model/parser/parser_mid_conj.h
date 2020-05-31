#include "../../public.h"
#include "parser.h"

namespace xforce { namespace nlu { namespace semantic {

class ParserMidConj : public Parser {
 protected:
  bool Filter_(basic::NluContext &nluContext);
  void Process_(basic::NluContext &nluContext);

 private:
  template <typename FragmentType>
  void ProcessFeature_(
          basic::NluContext &nluContext,
          std::shared_ptr<basic::Segment> &conj);

 private:
  std::vector<std::shared_ptr<basic::Segment>> conjs_;
};

bool ParserMidConj::Filter_(basic::NluContext &nluContext) {
  conjs_.clear();
  for (auto &segment : nluContext.Get<basic::Segment>().GetAll()) {
    bool prev, mid, post;
    if (segment->GetTag() == basic::PosTag::Type::kC &&
        basic::Manager::Get().GetGkb().GetGkbConj().Pos(
            segment->GetQuery(nluContext.GetQuery()), prev, mid, post)) {
      if (mid) {
        conjs_.push_back(segment);
      }
    }
  }
}

template <typename FragmentType>
void ParserMidConj::ProcessFeature_(
        basic::NluContext &nluContext,
        std::shared_ptr<basic::Segment> &conj) {
  std::vector<std::shared_ptr<FragmentType>> before;
  std::vector<std::shared_ptr<FragmentType>> after;
  nluContext.GetFragmentBefore(conj->GetOffset(), before);
  nluContext.GetFragmentAfter(conj->GetOffset(), after);
}

}}}