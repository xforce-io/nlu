#include "../pos_tag.h"

namespace xforce { namespace nlu { namespace basic {

PosTag::Type PosTag::GetPosTag(const std::wstring &pos) {
  switch (pos[0]) {
    case L'n' :
      return PosTag::kN;
    case L't' :  
      return PosTag::kT;
    case L's' :  
      return PosTag::kS;
    case L'f' :  
      return PosTag::kF;
    case L'm' :  
      return PosTag::kM;
    case L'q' :  
      return PosTag::kQ;
    case L'r' :  
      return PosTag::kR;
    case L'v' :  
      if (pos.length() == 2) {
        if (pos[1] == L'n') {
          return PosTag::kVn;
        }
      }
      return PosTag::kV;
    case L'a' :  
      return PosTag::kA;
    case L'z' :  
      return PosTag::kZ;
    case L'b' :  
      return PosTag::kB;
    case L'd' :  
      return PosTag::kD;
    case L'p' :  
      return PosTag::kP;
    case L'c' :  
      return PosTag::kC;
    case L'u' :  
      return PosTag::kU;
    case L'y' :  
      return PosTag::kY;
    case L'o' :  
      return PosTag::kO;
    case L'e' :  
      return PosTag::kE;
    case L'h' :  
      return PosTag::kH;
    case L'k' :  
      return PosTag::kK;
    case L'g' : {  
      if (pos == L"Vg") {
        return PosTag::kGv;
      } else if (pos == L"Vn") {
        return PosTag::kGn;
      }           
      return PosTag::kUndef;
    }
    case L'x' : 
      return PosTag::kX;
    case L'i' :  
      return PosTag::kI;
    case L'l' :  
      return PosTag::kL;
    case L'j' :  
      return PosTag::kJ;
    case L'w' :  
      return PosTag::kW;
    default :  
      return PosTag::kUndef;
  };
}

const std::wstring& PosTag::Str(PosTag::Type type) {
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
  switch (type) {
    case PosTag::kN :
      return kN;
    case PosTag::kT :
      return kT;  
    case PosTag::kS :
      return kS;  
    case PosTag::kF :
      return kF;  
    case PosTag::kM :
      return kM;  
    case PosTag::kQ :
      return kQ;  
    case PosTag::kR :
      return kR;  
    case PosTag::kV :
      return kV;  
    case PosTag::kVn :
      return kVn;  
    case PosTag::kA :
      return kA;  
    case PosTag::kZ :
      return kZ;  
    case PosTag::kB :
      return kB;  
    case PosTag::kD :
      return kD;  
    case PosTag::kP :
      return kP;  
    case PosTag::kC :
      return kC;  
    case PosTag::kU :
      return kU;  
    case PosTag::kY :
      return kY;  
    case PosTag::kO :
      return kO;  
    case PosTag::kE :
      return kE;  
    case PosTag::kH :
      return kH;  
    case PosTag::kK :
      return kK;  
    case PosTag::kGn :
      return kGn;  
    case PosTag::kGv :
      return kGv;  
    case PosTag::kX :
      return kX;  
    case PosTag::kI :
      return kI;  
    case PosTag::kL :
      return kL;  
    case PosTag::kJ :
      return kJ;  
    case PosTag::kW :
      return kW;  
    default :  
      return kUndef;
  }
}

}}}
