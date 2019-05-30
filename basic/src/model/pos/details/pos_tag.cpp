#include "../pos_tag.h"

namespace xforce { namespace nlu { namespace basic {

PosTag::Type::Val PosTag::GetPosTag(const std::wstring &posTag) {
  switch (posTag[0]) {
    case L'n' :
      return PosTag::Type::kN;
    case L't' :  
      return PosTag::Type::kT;
    case L's' :  
      return PosTag::Type::kS;
    case L'f' :  
      return PosTag::Type::kF;
    case L'm' :  
      return PosTag::Type::kM;
    case L'q' :  
      return PosTag::Type::kQ;
    case L'r' :  
      return PosTag::Type::kR;
    case L'v' :  
      if (posTag.length() == 2) {
        if (posTag[1] == L'n') {
          return PosTag::Type::kVn;
        }
      }
      return PosTag::Type::kV;
    case L'a' :  
      return PosTag::Type::kA;
    case L'z' :  
      return PosTag::Type::kZ;
    case L'b' :  
      return PosTag::Type::kB;
    case L'd' :  
      return PosTag::Type::kD;
    case L'p' :  
      return PosTag::Type::kP;
    case L'c' :  
      return PosTag::Type::kC;
    case L'u' :  
      return PosTag::Type::kU;
    case L'y' :  
      return PosTag::Type::kY;
    case L'o' :  
      return PosTag::Type::kO;
    case L'e' :  
      return PosTag::Type::kE;
    case L'h' :  
      return PosTag::Type::kH;
    case L'k' :  
      return PosTag::Type::kK;
    case L'x' :
      return PosTag::Type::kX;
    case L'i' :  
      return PosTag::Type::kI;
    case L'l' :  
      return PosTag::Type::kL;
    case L'j' :  
      return PosTag::Type::kJ;
    case L'w' :  
      return PosTag::Type::kW;
    default :  
      return PosTag::Type::kUndef;
  };
}

const std::wstring& PosTag::Str(PosTag::Type::Val posTag) {
  static const std::wstring kN = L"n";
  static const std::wstring kT = L"t";
  static const std::wstring kS = L"s";
  static const std::wstring kF = L"f";
  static const std::wstring kM = L"m";
  static const std::wstring kQ = L"q";
  static const std::wstring kR = L"r";
  static const std::wstring kV = L"v";
  static const std::wstring kVn = L"vn";
  static const std::wstring kA = L"a";
  static const std::wstring kZ = L"z";
  static const std::wstring kB = L"b";
  static const std::wstring kD = L"d";
  static const std::wstring kP = L"p";
  static const std::wstring kC = L"c";
  static const std::wstring kU = L"u";
  static const std::wstring kY = L"y";
  static const std::wstring kO = L"o";
  static const std::wstring kE = L"e";
  static const std::wstring kH = L"h";
  static const std::wstring kK = L"k";
  static const std::wstring kGn = L"gn";
  static const std::wstring kGv = L"gv";
  static const std::wstring kX = L"x";
  static const std::wstring kI = L"i";
  static const std::wstring kL = L"l";
  static const std::wstring kJ = L"j";
  static const std::wstring kW = L"w";
  static const std::wstring kUndef = L"undef";
  switch (posTag) {
    case PosTag::Type::kN :
      return kN;
    case PosTag::Type::kT :
      return kT;  
    case PosTag::Type::kS :
      return kS;  
    case PosTag::Type::kF :
      return kF;  
    case PosTag::Type::kM :
      return kM;  
    case PosTag::Type::kQ :
      return kQ;  
    case PosTag::Type::kR :
      return kR;  
    case PosTag::Type::kV :
      return kV;  
    case PosTag::Type::kVn :
      return kVn;  
    case PosTag::Type::kA :
      return kA;  
    case PosTag::Type::kZ :
      return kZ;  
    case PosTag::Type::kB :
      return kB;  
    case PosTag::Type::kD :
      return kD;  
    case PosTag::Type::kP :
      return kP;  
    case PosTag::Type::kC :
      return kC;  
    case PosTag::Type::kU :
      return kU;  
    case PosTag::Type::kY :
      return kY;  
    case PosTag::Type::kO :
      return kO;  
    case PosTag::Type::kE :
      return kE;  
    case PosTag::Type::kH :
      return kH;  
    case PosTag::Type::kK :
      return kK;  
    case PosTag::Type::kX :
      return kX;  
    case PosTag::Type::kI :
      return kI;  
    case PosTag::Type::kL :
      return kL;  
    case PosTag::Type::kJ :
      return kJ;  
    case PosTag::Type::kW :
      return kW;  
    default :  
      return kUndef;
  }
}

}}}
