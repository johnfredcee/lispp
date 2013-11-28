
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
	// constant literal 
	if (is_char(obj) ||	is_fixnum(obj) || is_floatnum(obj) || is_string(obj))
	  return obj;
	// symbol lookup
	if (is_symbol(obj)) {
		return env->ref(get_ctype<SymbolType>(obj).name); // ((LispSymbol)(boost::get<SymbolType>(*obj))).first);
	}
	// cons cell
	if (is_cons(obj)) 
	{
		// must be function invocation -- function symbol
		LispObjRef fnsym(car(obj));
		if (is_symbol(fnsym) || is_primitive(fnsym))
		{	
			LispObjRef fn = is_symbol(fnsym) ? env->fref(get_ctype<SymbolType>(fnsym).name) : fnsym;
			// it's a function
			if (is_primitive(fn)) {
				CPrim cfn = (CPrim)(boost::get<PrimType>(*fn));
				// call it on the cdr
				return cfn(cdr(obj), env);
			} // Else .. it's a lambda..
		}
	} 
	return nil;		
  };
}
