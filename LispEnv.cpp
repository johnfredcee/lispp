
#include "LispObj.h"
#include "LispEnv.h"

using namespace std;

namespace Lisp {

	LispEnvRef LispEnv::globalEnv(new LispEnv);

	LispEnv::LispEnv() : parent_(boost::shared_ptr<LispEnv>()) {
	}

	LispEnv::LispEnv(boost::shared_ptr<LispEnv> parentEnv] : parent_(parentEnv) {		
	}
	
	LispObjRef LispEnv::ref(std::string var)  {
		EnvironmentT::iterator it(env_.find(var));
		if (it != env_.end()) {
			return it->second;
		};
		if (parent_ != NULL) {
			return parent_->ref(var);
		} 
		LispObjRef nil;
		return nil;
	}	

	LispObjRef LispEnv::set(std::string var, LispObjRef ref) {
		env[var] = ref;
		return ref;
	}
	
}
