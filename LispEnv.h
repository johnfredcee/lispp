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

	/** fetch function in environment */
	LispObjRef fref(std::string var);

	/** Set a function in the environment */
	LispObjRef fset(std::string var, LispObjRef ref);	

	/** Set function primitive */
	static LispObjRef set_fn(LispObjRef cons, LispEnvRef env);

	/** Global environment */
	static LispEnvRef globalEnv;

  private:
		
	/** Our environemnt. */
	EnvironmentT env_;

	/** Our function environment (yes, it's a Lisp-2) */
	EnvironmentT fEnv_;

	/** Pointer back up to parent environment */
	LispEnvRef parent_;
  };	

}
#endif
