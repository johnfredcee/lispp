#ifndef LISPEVAL_H
#define LISPEVAL_H

#include "LispEnv.h"

namespace Lisp {
	class LispEnv;

	class Eval {
	public:		
		LispObjRef operator()(LispObjRef obj, LispEnvRef env);
	};
}
#endif
