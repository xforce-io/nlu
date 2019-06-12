#pragma once

#include "../../public.h"
#include "../pos_ctb/pos_ctb_tag.h"

namespace xforce { namespace nlu { namespace basic {

class SyntaxTag {
 public:
  enum Type {
      //pos tags
      kAd,
      kAs,
      kBa,
      kCc,
      kCd,
      kCs,
      kDec,
      kDeg,
      kDer,
      kDev,
      kDt,
      kEtc,
      kFw,
      kIj,
      kJj,
      kLb,
      kLc,
      kM,
      kMsp,
      kNn,
      kNr,
      kNt,
      kOd,
      kOn,
      kP,
      kPn,
      kPu,
      kSb,
      kSp,
      kVa,
      kVc,
      kVe,
      kVv,

      //syntax tags
      kAdjp, //Adjective phrase / 形容词短语
      kAdvp, //Adverbial phrase headed by AD (adverb) / 由副词开头的副词短语
      kClp, //Classifier phrase / 量词短语
      kCp, //Clause headed by C (complementizer) / 由补语引导的补语从句
      kDnp, //Phrase formed by “XP+DEG”
      kDp, //Determiner phrase / 限定词短语
      kDvp, //Phrase formed by “XP+DEV”
      kFrag, //fragment
      kIp, //Simple clause headed by I (INFL 或其曲折成分)
      kLcp, //Phrase formed by “XP+LC” / LC位置词
      kLst, //List marker / 列表标记，如“--”
      kNp, //Noun phrase / 名词短语
      kPp, //Preposition phrase / 介词短语
      kPrn, //Parenthetical / 括号中的，插入的
      kQp, //Quantifier phrase / 量词短语
      kUcp, //unidentical coordination phrase / 非对等同位语短语
      kVp, //Verb phrase / 动词短语
      kUndef,
  };

 public:
  static SyntaxTag::Type GetSyntaxTag(const std::wstring &syntaxTag);
  static SyntaxTag::Type GetSyntaxTag(basic::PosCtbTag::Type posCtbTag);
  static const std::wstring& Str(SyntaxTag::Type type);
};

}}}