#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace basic {

class PosCtb {
 public:
  enum Type {
    kAd, //adverbs / 副词
    kAs, //aspect marker / 体态词，体标记（例如：了，在，着，过）
    kBa, //把 in ba-const / “把”，“将”的词性标记
    kCc, //Coordinating conjunction / 并列连词，“和”
    kCd, //Cardinal numbers / 数字，“一百”
    kCs, //Subordinating conj / 从属连词 （例子：若，如果，如…）
    kDec, //的 for relative-clause etc / “的”词性标记
    kDeg, //Associative 的 / 联结词“的”
    kDer, //得 in V-de construction, and V-de-R / “得”
    kDev, //地 before VP / 地
    kDt, //Determiner / 限定词，“这”
    kEtc, //Tag for words 等，等等 in coordination phrase / 等，等等
    kFw, //Foreign words / 例子：ISO
    kIj, //interjection / 感叹词
    kJj, //Noun-modifier other than nouns /
    kLb, //被 in long bei-construction / 例子：被，给
    kLc, //Localizer / 定位词，例子：“里”
    kM, //Measure word (including classifiers) / 量词，例子：“个”
    kMsp, //Some particles / 例子：“所”
    kNn, //Common nouns / 普通名词
    kNr, //Proper nouns / 专有名词
    kNt, //Temporal nouns / 时序词，表示时间的名词
    kOd, //Ordinal numbers / 序数词，“第一”
    kOn, //Onomatopoeia / 拟声词，“哈哈”
    kP, //Prepositions (excluding 把 and 被) / 介词
    kPn, //pronouns / 代词
    kPu, //Punctuations / 标点
    kSb, //被in long bei-construction / 例子：“被，给”
    kSp, //Sentence-final particle / 句尾小品词，“吗”
    kVa, //Predicative adjective / 表语形容词，“红”
    kVc, //Copula 是 / 系动词，“是”
    kVe, //有 as the main verb / “有”
    kVv, //Other verbs / 其他动词
    kUndef,
  };
};

}}}