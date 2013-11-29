
#include "LispObj.h"
#include "LispEnv.h"
#include "LispNil.h"
#include "LispQuote.h"
#include "LispCons.h"
#include "LispSymbol.h"

using namespace std;

namespace Lisp {

// there is one global ennvironment at the root of everything
	LispEnvRef LispEnv::globalEnv = LispEnvRef(new LispEnv);

// constructor - new environment is constructed referring to
// it's parent, normally, but this is for the global environment
	LispEnv::LispEnv() : parent_(LispEnvRef()) {
		fEnv_["QUOTE"]   = make_literal(PrimType(LispQuote::quote_fn)); 
		fEnv_["SET!"]    = make_literal(PrimType(LispEnv::set_fn));     
		fEnv_["DEFINE"]  = make_literal(PrimType(LispEnv::define_fn));     
		fEnv_["DEFUN"]   = make_literal(PrimType(LispEnv::defun_fn));     
	}

// constructor - new environment created with parent
	LispEnv::LispEnv(LispEnvRef parentEnv) : parent_(parentEnv) {		
	}

// resolve a reference to a symbol in an environment	
// corresponds to lookup-variable-value in sicp
	LispObjRef LispEnv::ref(std::string var)  {
		EnvironmentT::iterator it(env_.find(var));
		if (it != env_.end()) {
			return it->second;
		};
		if (parent_ != NULL) {
			return parent_->ref(var);
		} 
		return nil;
	}	

	// bind a symnbol to a variable in this environment
	// corresponts to set-variable-value! in sicp
	LispObjRef LispEnv::set(std::string var, LispObjRef ref) {
		
		EnvironmentT::iterator it(env_.find(var));
		if (it != env_.end()) {
			it->second = ref;
			return ref;
		} else {
			if (parent_ != NULL)
				return parent_->set(var, ref);
		}
		return nil;
	}

	// bind a symnbol to a variable in this environment
	// corresponts to define in sicp
	LispObjRef LispEnv::define(std::string var, LispObjRef ref)
	{
		EnvironmentT::iterator it(env_.find(var));
		if (it != env_.end()) {
			it->second = ref;
		} else {
			env_[var] = ref;
		}
		return ref;
	}

	// resolve a reference to a function in an environment	
	LispObjRef LispEnv::fref(std::string var)  {
		EnvironmentT::iterator it(fEnv_.find(var));
		if (it != fEnv_.end()) {
			return it->second;
		};
		if (parent_ != NULL) {
			return parent_->fref(var);
		} 
		return nil;
	}	

	// set the value associated with a symbol in an environment
	LispObjRef LispEnv::fset(std::string var, LispObjRef ref) {
		fEnv_[var] = ref;
		return ref;
	}

	// Function used for the (set ) special form - bind car to cons
	LispObjRef LispEnv::set_fn(LispObjRef cons, LispEnvRef env) {
		// car of cons should be a symbol
		if (is_symbol(car(cons)))
			return env->set(get_ctype<SymbolType>(car(cons)).name, cdr(cons));
		return nil;
	}

	LispObjRef LispEnv::define_fn(LispObjRef cons, LispEnvRef env) 
	{
		if (is_symbol(car(cons)))
			return env->define(get_ctype<SymbolType>(car(cons)).name, cdr(cons));
		return nil;
	}

	LispObjRef LispEnv::defun_fn(LispObjRef cons, LispEnvRef env) 
	{
		if (is_symbol(car(cons)))
			return env->fset(get_ctype<SymbolType>(car(cons)).name, cdr(cons));
		return nil;
	}

}
