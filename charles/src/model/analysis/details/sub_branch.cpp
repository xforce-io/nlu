#include "../sub_branch.h"
#include "../analysis_clause.h"

namespace xforce { namespace nlu { namespace charles {

SubBranch::SubBranch(
        const basic::Chunk &chunk,
        std::shared_ptr<AnalysisClause> clause) :
    chunk_(chunk),
    clause_(clause) {}

}}}
