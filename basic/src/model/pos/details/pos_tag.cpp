#include "../pos_tag.h"

namespace xforce { namespace nlu { namespace basic {

PosTag::Type PosTag::GetPosTag(const std::string &pos) {
  switch (pos[0]) {
    case 'n' :
      return PosTag::kN;
    case 't' :  
      return PosTag::kT;
    case 's' :  
      return PosTag::kS;
    case 'f' :  
      return PosTag::kF;
    case 'm' :  
      return PosTag::kM;
    case 'q' :  
      return PosTag::kQ;
    case 'r' :  
      return PosTag::kR;
    case 'v' :  
      return PosTag::kV;
    case 'a' :  
      return PosTag::kA;
    case 'z' :  
      return PosTag::kZ;
    case 'b' :  
      return PosTag::kB;
    case 'd' :  
      return PosTag::kD;
    case 'p' :  
      return PosTag::kP;
    case 'c' :  
      return PosTag::kC;
    case 'u' :  
      return PosTag::kU;
    case 'y' :  
      return PosTag::kY;
    case 'o' :  
      return PosTag::kO;
    case 'e' :  
      return PosTag::kE;
    case 'h' :  
      return PosTag::kH;
    case 'k' :  
      return PosTag::kK;
    case 'g' : {  
      if (pos == "Vg") {
        return PosTag::kGv;
      } else if (pos == "Vn") {
        return PosTag::kGn;
      }           
      return PosTag::kUndef;
    }
    case 'x' :  
      return PosTag::kX;
    case 'i' :  
      return PosTag::kI;
    case 'l' :  
      return PosTag::kL;
    case 'j' :  
      return PosTag::kJ;
    case 'w' :  
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
