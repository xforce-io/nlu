#pragma once

#include "../../public.h"

namespace xforce { namespace nlu { namespace basic {

class PosTag {
 public: 
  enum Type {
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

 public:
  static PosTag::Type GetPosTag(const std::wstring &pos);
  static const std::wstring& Str(PosTag::Type posTag);
  inline static bool IsPred(PosTag::Type posTag);
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

bool PosTag::IsPred(PosTag::Type posTag) {
  return PosTag::kV == posTag ||
    PosTag::kA == posTag ||
    PosTag::kZ == posTag;
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
