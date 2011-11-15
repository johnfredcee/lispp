
#include "LispObj.h"
#include "LispEnv.h"
#include "LispNil.h"

using namespace std;

namespace Lisp {

// there is one global ennvironment at the root of everything
LispEnvRef LispEnv::globalEnv = LispEnvRef(new LispEnv);

// constructor - new environment is constructed referring to
// it's parent, normally, but this is for the global environment
LispEnv::LispEnv() : parent_(LispEnvRef()) {
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

// set the value associated with a symbol in an environment
LispObjRef LispEnv::set(std::string var, LispObjRef ref) {
	env_[var] = ref;
	return ref;
}
	
}
