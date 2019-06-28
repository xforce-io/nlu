#include "../syntax_tag.h"

namespace xforce { namespace nlu { namespace basic {

SyntaxTag::Type::Type::Val SyntaxTag::Type::GetSyntaxTag(const std::wstring &syntaxTag) {
  if (L"adjp" == syntaxTag) {
    return SyntaxTag::Type::Type::kAdjp;
  } else if (L"advp" == syntaxTag) {
    return SyntaxTag::Type::Type::kAdvp;
  } else if (L"clp" == syntaxTag) {
    return SyntaxTag::Type::Type::kClp;
  } else if (L"cp" == syntaxTag) {
    return SyntaxTag::Type::Type::kCp;
  } else if (L"dnp" == syntaxTag) {
    return SyntaxTag::Type::Type::kDnp;
  } else if (L"dp" == syntaxTag) {
    return SyntaxTag::Type::Type::kDp;
  } else if (L"dvp" == syntaxTag) {
    return SyntaxTag::Type::Type::kDvp;
  } else if (L"frag" == syntaxTag) {
    return SyntaxTag::Type::Type::kFrag;
  } else if (L"ip" == syntaxTag) {
    return SyntaxTag::Type::Type::kIp;
  } else if (L"lcp" == syntaxTag) {
    return SyntaxTag::Type::Type::kLcp;
  } else if (L"lst" == syntaxTag) {
    return SyntaxTag::Type::Type::kLst;
  } else if (L"np" == syntaxTag) {
    return SyntaxTag::Type::Type::kNp;
  } else if (L"pp" == syntaxTag) {
    return SyntaxTag::Type::Type::kPp;
  } else if (L"prn" == syntaxTag) {
    return SyntaxTag::Type::Type::kPrn;
  } else if (L"qp" == syntaxTag) {
    return SyntaxTag::Type::Type::kQp;
  } else if (L"ucp" == syntaxTag) {
    return SyntaxTag::Type::Type::kUcp;
  } else if (L"vp" == syntaxTag) {
    return SyntaxTag::Type::Type::kVp;
  } else if (L"_stc_" == syntaxTag) {
    return SyntaxTag::Type::Type::kStc;
  } else if (L"_cont_np_" == syntaxTag) {
    return SyntaxTag::Type::Type::kContNp;
  } else {
    return SyntaxTag::Type::Type::kUndef;
  }
}

const std::wstring& SyntaxTag::Type::Str(SyntaxTag::Type::Type::Val syntaxTag) {
  static const std::wstring kAdjp = L"adjp";
  static const std::wstring kAdvp = L"advp";
  static const std::wstring kClp = L"clp";
  static const std::wstring kCp = L"cp";
  static const std::wstring kDnp = L"dnp";
  static const std::wstring kDp = L"dp";
  static const std::wstring kDvp = L"dvp";
  static const std::wstring kFrag = L"frag";
  static const std::wstring kIp = L"ip";
  static const std::wstring kLcp = L"lcp";
  static const std::wstring kLst = L"lst";
  static const std::wstring kNp = L"np";
  static const std::wstring kPp = L"pp";
  static const std::wstring kPrn = L"prn";
  static const std::wstring kQp = L"qp";
  static const std::wstring kUcp = L"ucp";
  static const std::wstring kVp = L"vp";
  static const std::wstring kStc = L"_stc_";
  static const std::wstring kContNp = L"_cont_np_";
  static const std::wstring kUndef = L"undef";
  switch (syntaxTag) {
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
