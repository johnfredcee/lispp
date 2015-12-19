
#include <cassert>

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <utility>

#include "LispObj.h"
#include "LispNil.h"
#include "LispCons.h"

namespace Lisp
{

LispObjRef make_cons(LispObjRef car, LispObjRef cdr) {
	return boost::shared_ptr<LispObj>(new LispObj(std::pair<LispObjRef, LispObjRef>(car,cdr)));
}

LispObjRef car(LispObjRef cons) {
	assert(is_cons(cons));
	return get_ctype<ConsType>(cons).first;
}

LispObjRef cdr(LispObjRef cons) {
	assert(is_cons(cons));
	return get_ctype<ConsType>(cons).second;
}

LispObjRef cadr(LispObjRef cons) {
	assert(is_cons(cons));
	LispObjRef ncar = get_ctype<ConsType>(cons).second;
	assert(is_cons(ncar) | is_nil(ncar));
	return !is_nil(ncar) ? car(ncar) : nil;
}

LispObjRef cddr(LispObjRef cons) {
	assert(is_cons(cons));
	LispObjRef ncar = get_ctype<ConsType>(cons).second;
	assert(is_cons(ncar));
	ncar = get_ctype<ConsType>(cons).second;	
	return ncar;
}

bool is_cons(LispObjRef obj) {
	return (obj->which() == CONS);
}

}
