#include "../pos.h"

namespace xforce { namespace nlu { namespace basic {

Pos::Type Pos::GetPos(const std::string &pos) {
  switch (pos[0]) {
    case 'n' :
      return Pos::kN;
    case 't' :  
      return Pos::kT;
    case 's' :  
      return Pos::kS;
    case 'f' :  
      return Pos::kF;
    case 'm' :  
      return Pos::kM;
    case 'q' :  
      return Pos::kQ;
    case 'r' :  
      return Pos::kR;
    case 'v' :  
      return Pos::kV;
    case 'a' :  
      return Pos::kA;
    case 'z' :  
      return Pos::kZ;
    case 'b' :  
      return Pos::kB;
    case 'd' :  
      return Pos::kD;
    case 'p' :  
      return Pos::kP;
    case 'c' :  
      return Pos::kC;
    case 'u' :  
      return Pos::kU;
    case 'y' :  
      return Pos::kY;
    case 'o' :  
      return Pos::kO;
    case 'e' :  
      return Pos::kE;
    case 'h' :  
      return Pos::kH;
    case 'k' :  
      return Pos::kK;
    case 'g' : {  
      if (pos == "Vg") {
        return Pos::kGv;
      } else if (pos == "Vn") {
        return Pos::kGn;
      }           
      return Pos::kUndef;
    }
    case 'x' :  
      return Pos::kX;
    case 'i' :  
      return Pos::kI;
    case 'l' :  
      return Pos::kL;
    case 'j' :  
      return Pos::kJ;
    case 'w' :  
      return Pos::kW;
    default :  
      return Pos::kUndef;
  };
}

const std::wstring& Pos::Str(Pos::Type type) {
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
    case Pos::kN :
      return kN;
    case Pos::kT :
      return kT;  
    case Pos::kS :
      return kS;  
    case Pos::kF :
      return kF;  
    case Pos::kM :
      return kM;  
    case Pos::kQ :
      return kQ;  
    case Pos::kR :
      return kR;  
    case Pos::kV :
      return kV;  
    case Pos::kA :
      return kA;  
    case Pos::kZ :
      return kZ;  
    case Pos::kB :
      return kB;  
    case Pos::kD :
      return kD;  
    case Pos::kP :
      return kP;  
    case Pos::kC :
      return kC;  
    case Pos::kU :
      return kU;  
    case Pos::kY :
      return kY;  
    case Pos::kO :
      return kO;  
    case Pos::kE :
      return kE;  
    case Pos::kH :
      return kH;  
    case Pos::kK :
      return kK;  
    case Pos::kGn :
      return kGn;  
    case Pos::kGv :
      return kGv;  
    case Pos::kX :
      return kX;  
    case Pos::kI :
      return kI;  
    case Pos::kL :
      return kL;  
    case Pos::kJ :
      return kJ;  
    case Pos::kW :
      return kW;  
    default :  
      return kUndef;
  }
}

}}}
