
#include "LispObj.h"
#include "LispEnv.h"
#include "LispNil.h"
#include "LispQuote.h"
using namespace std;

namespace Lisp {

// there is one global ennvironment at the root of everything
LispEnvRef LispEnv::globalEnv = LispEnvRef(new LispEnv);

// constructor - new environment is constructed referring to
// it's parent, normally, but this is for the global environment
LispEnv::LispEnv() : parent_(LispEnvRef()) {
	fEnv_["QUOTE"] = LispObjRef(static_cast<LispObj*>(new LispObj(PrimType(LispQuote::quote_fn)));
}

// constructor - new environment created with parent
LispEnv::LispEnv(LispEnvRef parentEnv) : parent_(parentEnv) {		
}

// resolve a reference to a symbol in an environment	
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

// resolve a reference to a function in an environment	
LispObjRef LispEnv::fref(std::string var)  {
	EnvironmentT::iterator it(env_.find(var));
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
	
}
