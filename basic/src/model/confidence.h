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
  inline bool Gt(const Confidence &confidence) const;
  inline bool Ge(const Confidence &confidence) const;
  inline bool Lt(const Confidence &confidence) const;
  inline bool Le(const Confidence &confidence) const;
  inline bool Eq(const Confidence &confidence) const;

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

bool Confidence::Gt(const Confidence &confidence) const {
  return score_ > confidence.GetScore();
}

bool Confidence::Ge(const Confidence &confidence) const {
  return score_ >= confidence.GetScore();
}

bool Confidence::Lt(const Confidence &confidence) const {
  return score_ < confidence.GetScore();
}

bool Confidence::Le(const Confidence &confidence) const {
  return score_ <= confidence.GetScore();
}

bool Confidence::Eq(const Confidence &confidence) const {
  return score_ == confidence.GetScore();
}

}}}
