#include "../syntax_tag.h"

namespace xforce { namespace nlu { namespace basic {

SyntaxTag::Type::Val SyntaxTag::GetSyntaxTag(const std::wstring &syntaxTag) {
  if (L"p" == syntaxTag) {
    return SyntaxTag::Type::kP;
  } else if (L"v" == syntaxTag) {
    return SyntaxTag::Type::kV;
  } else if (L"vw" == syntaxTag) {
    return SyntaxTag::Type::kVw;
  } else if (L"adjp" == syntaxTag) {
    return SyntaxTag::Type::kAdjp;
  } else if (L"advp" == syntaxTag) {
    return SyntaxTag::Type::kAdvp;
  } else if (L"clp" == syntaxTag) {
    return SyntaxTag::Type::kClp;
  } else if (L"cp" == syntaxTag) {
    return SyntaxTag::Type::kCp;
  } else if (L"dnp" == syntaxTag) {
    return SyntaxTag::Type::kDnp;
  } else if (L"dp" == syntaxTag) {
    return SyntaxTag::Type::kDp;
  } else if (L"dt" == syntaxTag) {
    return SyntaxTag::Type::kDt;
  } else if (L"dvp" == syntaxTag) {
    return SyntaxTag::Type::kDvp;
  } else if (L"frag" == syntaxTag) {
    return SyntaxTag::Type::kFrag;
  } else if (L"ip" == syntaxTag) {
    return SyntaxTag::Type::kIp;
  } else if (L"lcp" == syntaxTag) {
    return SyntaxTag::Type::kLcp;
  } else if (L"lst" == syntaxTag) {
    return SyntaxTag::Type::kLst;
  } else if (L"np" == syntaxTag) {
    return SyntaxTag::Type::kNp;
  } else if (L"pp" == syntaxTag) {
    return SyntaxTag::Type::kPp;
  } else if (L"prn" == syntaxTag) {
    return SyntaxTag::Type::kPrn;
  } else if (L"qp" == syntaxTag) {
    return SyntaxTag::Type::kQp;
  } else if (L"tp" == syntaxTag) {
    return SyntaxTag::Type::kTp;
  } else if (L"tt" == syntaxTag) {
    return SyntaxTag::Type::kTt;
  } else if (L"u" == syntaxTag) {
    return SyntaxTag::Type::kU;
  } else if (L"ucp" == syntaxTag) {
    return SyntaxTag::Type::kUcp;
  } else if (L"vp" == syntaxTag) {
    return SyntaxTag::Type::kVp;
  } else if (L"_stc_" == syntaxTag) {
    return SyntaxTag::Type::kStc;
  } else if (L"_cont_np_" == syntaxTag) {
    return SyntaxTag::Type::kContNp;
  } else {
    return SyntaxTag::Type::kUndef;
  }
}

const std::wstring& SyntaxTag::Str(SyntaxTag::Type::Val syntaxTag) {
  static const std::wstring kP = L"p";
  static const std::wstring kV = L"v";
  static const std::wstring kVw = L"vw";
  static const std::wstring kAdjp = L"adjp";
  static const std::wstring kAdvp = L"advp";
  static const std::wstring kClp = L"clp";
  static const std::wstring kCp = L"cp";
  static const std::wstring kDnp = L"dnp";
  static const std::wstring kDp = L"dp";
  static const std::wstring kDt = L"dt";
  static const std::wstring kDvp = L"dvp";
  static const std::wstring kFrag = L"frag";
  static const std::wstring kIp = L"ip";
  static const std::wstring kLcp = L"lcp";
  static const std::wstring kLst = L"lst";
  static const std::wstring kNp = L"np";
  static const std::wstring kPp = L"pp";
  static const std::wstring kPrn = L"prn";
  static const std::wstring kQp = L"qp";
  static const std::wstring kTp = L"tp";
  static const std::wstring kTt = L"tt";
  static const std::wstring kU = L"u";
  static const std::wstring kUcp = L"ucp";
  static const std::wstring kVp = L"vp";
  static const std::wstring kStc = L"_stc_";
  static const std::wstring kContNp = L"_cont_np_";
  static const std::wstring kUndef = L"undef";
  switch (syntaxTag) {
    case SyntaxTag::Type::kP :
      return kP;
    case SyntaxTag::Type::kV :
      return kV;
    case SyntaxTag::Type::kVw :
      return kVw;
    case SyntaxTag::Type::kAdjp :
      return kAdjp;
    case SyntaxTag::Type::kAdvp :
      return kAdvp;
    case SyntaxTag::Type::kClp :
      return kClp;
    case SyntaxTag::Type::kCp :
      return kCp;
    case SyntaxTag::Type::kDnp :
      return kDnp;
    case SyntaxTag::Type::kDp :
      return kDp;
    case SyntaxTag::Type::kDt :
      return kDt;
    case SyntaxTag::Type::kDvp :
      return kDvp;
    case SyntaxTag::Type::kFrag :
      return kFrag;
    case SyntaxTag::Type::kIp :
      return kIp;
    case SyntaxTag::Type::kLcp :
      return kLcp;
    case SyntaxTag::Type::kLst :
      return kLst;
    case SyntaxTag::Type::kNp :
      return kNp;
    case SyntaxTag::Type::kPp :
      return kPp;
    case SyntaxTag::Type::kPrn :
      return kPrn;
    case SyntaxTag::Type::kQp :
      return kQp;
    case SyntaxTag::Type::kTp :
      return kTp;
    case SyntaxTag::Type::kTt :
      return kTt;
    case SyntaxTag::Type::kU :
      return kU;
    case SyntaxTag::Type::kUcp :
      return kUcp;
    case SyntaxTag::Type::kVp :
      return kVp;
    case SyntaxTag::Type::kStc :
      return kStc;
    case SyntaxTag::Type::kContNp :
      return kContNp;
    default:
      return kUndef;
  }
}

}}}
