
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

LispObjRef car(LispObjRef cons) {
	return ((CCons)(boost::get<ConsType>(*cons))).first;
}

LispObjRef cdr(LispObjRef cons) {
	return ((CCons)(boost::get<ConsType>(*cons))).second;
}

bool is_cons(LispObjRef obj) {
	return (obj->which() == CONS);
}
}
