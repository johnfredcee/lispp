#ifndef LISPENV_H
#define LISPENV_H

#include <string>
#include <boost/tr1/memory.hpp>
#include <boost/unordered_map.hpp>
#include "LispObj.h"

namespace Lisp {
	class LispEnv;

	typedef boost::shared_ptr<LispEnv> LispEnvRef;

	class LispEnv {
	public:
		typedef boost::unordered_map<std::string, LispObjRef> EnvironmentT;

		/** construct root environment */
		LispEnv();

		/** construct child environment from parent */
		LispEnv(LispEnvRef parentEnv);

		/** fetch var in environment */
		LispObjRef ref(std::string var);

		/** Set a var in the environment */
		LispObjRef set(std::string var, LispObjRef ref);	
		
		/** Global environment */

		static LispEnvRef globalEnv;
	private:
		
		/** Our environemnt. */
		EnvironmentT env_;

		/** Pointer back up to parent environment */
		LispEnvRef parent_;
	};	

}
#endif
