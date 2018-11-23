#pragma once

#include "public.h"

namespace xforce { namespace nlu { namespace charles {

class Pos {
 public: 
  enum Type {
    /*
     * 实词/体词
     */
    kN, //名词
    kT, //时间词
    kS, //处所词
    kF, //方位词
    kM, //数词
    kQ, //量词
    kR, //代词

    /*
     * 实词/谓词
     */
    kV, //动词
    kA, //形容词
    kZ, //状态词

    /*
     * 实词
     */
    kB, //区别词
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
    kG, //语素
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
  }; 
};


}}}
