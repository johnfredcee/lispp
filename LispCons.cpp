
#include <cassert>

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <utility>

#include "LispObj.h"
#include "LispCons.h"

namespace Lisp
{

	LispObjRef make_cons(LispObjRef car, LispObjRef cdr) {
		return boost::shared_ptr<LispObj>(new LispObj(ConsType(std::pair<LispObjRef, LispObjRef>(car,cdr))));
	}

	bool is_cons(LispObjRef obj) {
		return (obj->which() == CONS);
	}
}
