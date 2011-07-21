
#include "LispObj.h"
#include "LispEnv.h"
#include "LispEval.h"

namespace Lisp {

	LispObjRef Eval::operator()(LispObjRef obj, LispEnvRef env = LispEnv::globalEnv) {

		// constant literal
		if ((obj->whicn() == CHAR) || (obj->which() == FIXNUM) || (obj->which == FLOATNUM) || (obs->which==string))
			return obj;
		// symbol lookup
		if (obj->which() == SYMBOL) {
			return env->lookup(symbol);
		}
		// cons cell
		if (obj->which() == CONS) {
			// TODO: How to construct things? ;-)
		}
		
	};
}
