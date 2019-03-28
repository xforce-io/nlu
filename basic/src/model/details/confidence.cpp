#include "../confidence.h"

namespace xforce { namespace nlu { namespace basic {

const Confidence Confidence::kFull = Confidence(100);
const Confidence Confidence::kHighlyConvinced = Confidence(99);
const Confidence Confidence::kConvinced = Confidence(95);
const Confidence Confidence::kProbable = Confidence(90);
const Confidence Confidence::kLikely = Confidence(80);
const Confidence Confidence::kPossible = Confidence(60);
const Confidence Confidence::kImpossible = Confidence(0);
const Confidence Confidence::kUninit = Confidence(-1);

}}}
