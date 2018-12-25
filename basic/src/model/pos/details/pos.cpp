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

const std::string& Pos::Str(Pos::Type type) {
  static const std::string kN = "n";
  static const std::string kT = "t";
  static const std::string kS = "s";
  static const std::string kF = "f";
  static const std::string kM = "m";
  static const std::string kQ = "q";
  static const std::string kR = "r";
  static const std::string kV = "v";
  static const std::string kA = "a";
  static const std::string kZ = "z";
  static const std::string kB = "b";
  static const std::string kD = "d";
  static const std::string kP = "p";
  static const std::string kC = "c";
  static const std::string kU = "u";
  static const std::string kY = "y";
  static const std::string kO = "o";
  static const std::string kE = "e";
  static const std::string kH = "h";
  static const std::string kK = "k";
  static const std::string kGn = "gn";
  static const std::string kGv = "gv";
  static const std::string kX = "x";
  static const std::string kI = "i";
  static const std::string kL = "l";
  static const std::string kJ = "j";
  static const std::string kW = "w";
  static const std::string kUndef = "undef";
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
