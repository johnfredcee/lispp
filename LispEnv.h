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
		LispEnv();
		LispEnv(boost::shared_ptr<LispEnv> parentEnv);
		LispObjRef ref(std::string var);
		LispObjRef set(std::string var, LispObjRef ref);	
		static boost::shared_ptr<LispEnv> globalEnv;
	private:
		EnvironmentT env_;
		LispEnvRef parent_;
	};	

}
#endif
