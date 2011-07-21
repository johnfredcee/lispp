#ifndef LISPEVAL_H
#define LISPEVAL_H

namespace Lisp {
	class Eval {
	public:		
		LispObj operator()(LispObj& obj, LispEnv& env);
	};
}
#endif
