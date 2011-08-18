
#include "LispObj.h"
#include "LispEnv.h"
#include "LispNil.h"

using namespace std;

namespace Lisp {

	LispEnvRef LispEnv::globalEnv = LispEnvRef(new LispEnv);

	LispEnv::LispEnv() : parent_(LispEnvRef()) {
	}

	LispEnv::LispEnv(LispEnvRef parentEnv) : parent_(parentEnv) {		
	}
	
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

	LispObjRef LispEnv::set(std::string var, LispObjRef ref) {
		env_[var] = ref;
		return ref;
	}
	
}
