
#include "LispObj.h"
#include "LispNil.h"
#include "LispChar.h"
#include "LispCons.h"
#include "LispEnv.h"
#include "LispFixNum.h"
#include "LispFloatNum.h"
#include "LispString.h"
#include "LispSymbol.h"
#include "LispPrimitive.h"
#include "LispEval.h"

namespace Lisp {

	LispObjRef Eval::operator()(LispObjRef obj, LispEnvRef env = LispEnv::globalEnv) {

		// trivial case :-)
		if (is_nil(obj))
			return nil;
		// constant literal (TODO: shoukd be using is<type> predicates)
		if (is_char(obj) ||	is_fixnum(obj) || is_floatnum(obj)  || is_string(obj))
			return obj;
		// symbol lookup
		if (is_symbol(obj)) {
			return env->ref(((LispSymbol)(boost::get<SymbolType>(*obj))).first);
		}
		// cons cell
		if (is_cons(obj)) {
			LispObjRef fnsym(car(obj));
			LispObjRef fn = env->fref(((LispSymbol)(boost::get<SymbolType>(*fnsym))).first);
			if (is_primitive(fn)) {
				CPrim cfn = (CPrim)(boost::get<PrimType>(*fn));
				return cfn((*this)(cdr(obj), env));
			} else {
				return make_cons((*this)(car(obj)), (*this)(cdr(obj), env));
			}
		}
		return nil;		
	};
}
