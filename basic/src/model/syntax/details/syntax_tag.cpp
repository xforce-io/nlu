#include "../syntax_tag.h"

namespace xforce { namespace nlu { namespace basic {

SyntaxTag::Type SyntaxTag::GetSyntaxTag(const std::wstring &syntaxTag) {
  if (L"adjp" == syntaxTag) {
    return SyntaxTag::kAdjp;
  } else if (L"advp" == syntaxTag) {
    return SyntaxTag::kAdvp;
  } else if (L"clp" == syntaxTag) {
    return SyntaxTag::kClp;
  } else if (L"cp" == syntaxTag) {
    return SyntaxTag::kCp;
  } else if (L"dnp" == syntaxTag) {
    return SyntaxTag::kDnp;
  } else if (L"dp" == syntaxTag) {
    return SyntaxTag::kDp;
  } else if (L"dvp" == syntaxTag) {
    return SyntaxTag::kDvp;
  } else if (L"frag" == syntaxTag) {
    return SyntaxTag::kFrag;
  } else if (L"ip" == syntaxTag) {
    return SyntaxTag::kIp;
  } else if (L"lcp" == syntaxTag) {
    return SyntaxTag::kLcp;
  } else if (L"lst" == syntaxTag) {
    return SyntaxTag::kLst;
  } else if (L"np" == syntaxTag) {
    return SyntaxTag::kNp;
  } else if (L"pp" == syntaxTag) {
    return SyntaxTag::kPp;
  } else if (L"prn" == syntaxTag) {
    return SyntaxTag::kPrn;
  } else if (L"qp" == syntaxTag) {
    return SyntaxTag::kQp;
  } else if (L"ucp" == syntaxTag) {
    return SyntaxTag::kUcp;
  } else if (L"vp" == syntaxTag) {
    return SyntaxTag::kVp;
  } else if (L"_stc_" == syntaxTag) {
    return SyntaxTag::kStc;
  } else if (L"_cont_np_" == syntaxTag) {
    return SyntaxTag::kContNp;
  } else {
    return SyntaxTag::kUndef;
  }
}

const std::wstring& SyntaxTag::Str(SyntaxTag::Type type) {
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
  switch (type) {
    case SyntaxTag::kAdjp :
      return kAdjp;
    case SyntaxTag::kAdvp :
      return kAdvp;
    case SyntaxTag::kClp :
      return kClp;
    case SyntaxTag::kCp :
      return kCp;
    case SyntaxTag::kDnp :
      return kDnp;
    case SyntaxTag::kDp :
      return kDp;
    case SyntaxTag::kDvp :
      return kDvp;
    case SyntaxTag::kFrag :
      return kFrag;
    case SyntaxTag::kIp :
      return kIp;
    case SyntaxTag::kLcp :
      return kLcp;
    case SyntaxTag::kLst :
      return kLst;
    case SyntaxTag::kNp :
      return kNp;
    case SyntaxTag::kPp :
      return kPp;
    case SyntaxTag::kPrn :
      return kPrn;
    case SyntaxTag::kQp :
      return kQp;
    case SyntaxTag::kUcp :
      return kUcp;
    case SyntaxTag::kVp :
      return kVp;
    case SyntaxTag::kStc :
      return kStc;
    case SyntaxTag::kContNp :
      return kContNp;
    default:
      return kUndef;
  }
}

}}}
