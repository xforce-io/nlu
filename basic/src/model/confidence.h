#pragma once

namespace xforce { namespace nlu { namespace basic {

class Confidence {
 public:
  static const Confidence kFull;
  static const Confidence kHighlyConvinced;
  static const Confidence kConvinced;
  static const Confidence kProbable;
  static const Confidence kLikely;
  static const Confidence kPossible;
  static const Confidence kImpossible;
  static const Confidence kUninit;

  inline Confidence();
  inline Confidence(int score);

  inline void SetScore(int score);
  int GetScore() const { return score_; }

 private:
  int score_;
};

Confidence::Confidence() :
  score_(-1) {}

Confidence::Confidence(int score) :
  score_(score) {}

void Confidence::SetScore(int score) {
  score_ = score;
}

}}}
