
#include "LispObj.h"

#include "LispEval.h"

namespace Lisp {

	LispObjRef Eval::operator()(LispObjRef obj, LispEnvRef env = LispEnv::globalEnv) {

		// constant literal (TODO: shoukd be using is<type> predicates)
		if ((obj->which() == CHAR)	 || 
			(obj->which() == FIXNUM) || 
			(obj->which() == FLOATNUM) || 
			(obj->which() == STRING))
			return obj;
		// symbol lookup
		if (obj->which() == SYMBOL) {
			return env->ref( ((LispSymbol)(boost::get<SymbolType>(*obj))).first) ;
		}
		// cons cell
		if (obj->which() == CONS) {
			// TODO: How to construct things? ;-)
		}
		
	};
}
