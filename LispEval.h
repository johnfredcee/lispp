#ifndef LISPEVAL_H
#define LISPEVAL_H

#include "LispEnv.h"

namespace Lisp {

class LispEnv;

class Eval {
public:		
	LispObjRef operator()(LispObjRef obj, LispEnvRef env = LispEnv::globalEnv, bool fplace = false);
};

extern Lisp::Eval    eval;

}
#endif
