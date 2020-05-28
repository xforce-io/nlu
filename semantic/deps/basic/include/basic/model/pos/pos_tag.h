#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace basic {

class PosTag {
 public: 
  struct Type {
    enum Val {
      /*
       * 实词/体词
       */
      kN = 0, //名词
      kT, //时间词
      kS, //处所词
      kF, //方位词
      kM, //数词
      kQ, //量词
      kR, //代词
      kRn, //体词性代词
      kRp, //谓词性代词

      /*
       * 实词/谓词
       */
      kV = 10, //动词
      kVn = 11, //动词
      kA, //形容词
      kZ, //状态词

      /*
       * 实词
       */
      kB = 20, //区别词
      kD, //副词

      /*
       * 虚词
       */
      kP, //介词
      kC, //连词
      kU, //助词
      kY, //语气词

      /*
       */
      kO, //拟声词
      kE, //叹词

      /*
       * 附加类别/小于词的单位
       */
      kH, //前接成分
      kK, //后接成分
      kG,
      kX, //非语素字

      /*
       * 附加类别/大于词的单位
       */
      kI, //成语
      kL, //习用语
      kJ, //简称略语

      /*
       * 标点符号
       */
      kW, //标点符号

      /*
       * 未定义
       */
      kUndef,
    };

    inline static bool IsSpecial(PosTag::Type::Val tagVal);
  };

  struct Class {
    enum Val {
      kNominal,
      kPredicate,
      kAdv,
      kFuncWord,
      kMood,
      kTime,
      kAppendixSubword,
      kAppendixIdiom,
      kPunctuation,
      kUndef,
    };
  };

 public:
  static PosTag::Type::Val GetPosTag(const std::wstring &pos);
  static PosTag::Type::Val GetPosTag(
          const std::wstring &pos,
          const std::wstring &word);
  static PosTag::Type::Val EnhancePosTag(
          PosTag::Type::Val posTag,
          const std::wstring &word);
  static PosTag::Type::Val GetPosTagFromChar(wchar_t pos);
  static const std::wstring& Str(PosTag::Type::Val posTag);

  inline static bool IsNominal(PosTag::Type::Val posTag);
  inline static bool IsPredicate(PosTag::Type::Val posTag);
  inline static bool IsAdv(PosTag::Type::Val posTag);
  inline static bool IsFuncWord(PosTag::Type::Val posTag);
  inline static bool IsMood(PosTag::Type::Val posTag);
  inline static bool IsTime(PosTag::Type::Val posTag);
  inline static bool IsAppendixSubword(PosTag::Type::Val posTag);
  inline static bool IsAppendixIdiom(PosTag::Type::Val posTag);
  inline static bool IsPunctuation(PosTag::Type::Val posTag);

  inline static PosTag::Class::Val GetClass(PosTag::Type::Val posTag);
};

class NotionOrForm {
 public: 
  enum Type {
    kNotion,
    kForm,
    kOther,
  };

 public:
  inline static NotionOrForm::Type GetNotionOrForm(
      const std::string &notionOrForm); 
};

class NominalOrPredicate {
 public: 
  enum Type {
    kNominal,
    kPredicate,
    kOther,
  };

 public:
  inline static NominalOrPredicate::Type GetNominalOrPredicate(
      const std::string &nominalOrPredicate); 
};

class SingleOrCompound {
 public: 
  enum Type {
    kSingle,
    kCompound,
    kOther,
  };

 public:
  inline static SingleOrCompound::Type GetSingleOrCompound(
      const std::string &singleOrCompound); 
};

bool PosTag::Type::IsSpecial(PosTag::Type::Val tagVal) {
  return tagVal == PosTag::Type::kUndef;
}

bool PosTag::IsNominal(PosTag::Type::Val posTag) {
  return PosTag::Type::kN == posTag ||
    PosTag::Type::kVn == posTag ||
    PosTag::Type::kT == posTag ||
    PosTag::Type::kS == posTag ||
    PosTag::Type::kF == posTag ||
    PosTag::Type::kM == posTag ||
    PosTag::Type::kQ == posTag ||
    PosTag::Type::kRn == posTag ||
    PosTag::Type::kH == posTag ||
    PosTag::Type::kK == posTag;
}

bool PosTag::IsPredicate(PosTag::Type::Val posTag) {
  return PosTag::Type::kRp == posTag ||
    PosTag::Type::kV == posTag ||
    PosTag::Type::kA == posTag ||
    PosTag::Type::kZ == posTag ||
    PosTag::Type::kB == posTag;
}

bool PosTag::IsAdv(PosTag::Type::Val posTag) {
  return PosTag::Type::kD == posTag;
}

bool PosTag::IsFuncWord(PosTag::Type::Val posTag) {
  return PosTag::Type::kP == posTag ||
    PosTag::Type::kC == posTag ||
    PosTag::Type::kU == posTag ||
    PosTag::Type::kY == posTag;
}

bool PosTag::IsMood(PosTag::Type::Val posTag) {
  return PosTag::Type::kO == posTag ||
    PosTag::Type::kE == posTag;
}

bool PosTag::IsTime(PosTag::Type::Val posTag) {
  return PosTag::Type::kT == posTag;
}

bool PosTag::IsAppendixSubword(PosTag::Type::Val posTag) {
  return PosTag::Type::kH == posTag ||
    PosTag::Type::kK == posTag ||
    PosTag::Type::kG == posTag ||
    PosTag::Type::kX == posTag;
}

bool PosTag::IsAppendixIdiom(PosTag::Type::Val posTag) {
  return PosTag::Type::kI == posTag ||
    PosTag::Type::kL == posTag ||
    PosTag::Type::kJ == posTag;
}

bool PosTag::IsPunctuation(PosTag::Type::Val posTag) {
  return PosTag::Type::kW == posTag;
}

PosTag::Class::Val PosTag::GetClass(PosTag::Type::Val posTag) {
  if (IsNominal(posTag)) {
    return PosTag::Class::kNominal;
  } else if (IsPredicate(posTag)) {
    return PosTag::Class::kPredicate;
  } else if (IsAdv(posTag)) {
    return PosTag::Class::kAdv;
  } else if (IsFuncWord(posTag)) {
    return PosTag::Class::kFuncWord;
  } else if (IsMood(posTag)) {
    return PosTag::Class::kMood;
  } else if (IsTime(posTag)) {
    return PosTag::Class::kTime;
  } else if (IsAppendixSubword(posTag)) {
    return PosTag::Class::kAppendixSubword;
  } else if (IsAppendixIdiom(posTag)) {
    return PosTag::Class::kAppendixIdiom;
  } else if (IsPunctuation(posTag)) {
    return PosTag::Class::kPunctuation;
  } else {
    return PosTag::Class::kUndef;
  }
}

NotionOrForm::Type NotionOrForm::GetNotionOrForm(
      const std::string &notionOrForm) {
  if (notionOrForm == "notion") {
    return NotionOrForm::kNotion;
  } else if (notionOrForm == "form") {
    return NotionOrForm::kForm;
  } else {
    return NotionOrForm::kOther;
  }
}

NominalOrPredicate::Type NominalOrPredicate::GetNominalOrPredicate(
      const std::string &nominalOrPredicate) {
  if (nominalOrPredicate == "nominal") {
    return NominalOrPredicate::kNominal;
  } else if (nominalOrPredicate == "predicate") {
    return NominalOrPredicate::kPredicate;
  } else {
    return NominalOrPredicate::kOther;
  }
}

SingleOrCompound::Type SingleOrCompound::GetSingleOrCompound(
      const std::string &singleOrCompound) {
  if (singleOrCompound == "single") {
    return SingleOrCompound::kSingle;
  } else if (singleOrCompound == "compound") {
    return SingleOrCompound::kCompound;
  } else {
    return SingleOrCompound::kOther;
  }
}

}}}
