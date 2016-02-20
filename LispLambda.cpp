
#include <cassert>

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <utility>

#include "LispObj.h"
#include "LispNil.h"
#include "LispCons.h"
#include "LispLambda.h"

namespace Lisp
{

LispObjRef make_lambda(LispObjRef args, LispObjRef body) {
	return boost::shared_ptr<LispObj>(new LispObj(Lambda(args,body)));
}

LispObjRef args(LispObjRef lambda) {
	assert(is_lambda(lambda));
	return get_ctype<LambdaType>(lambda).args;
}

LispObjRef body(LispObjRef lambda) {
	assert(is_lambda(lambda));
	return get_ctype<LambdaType>(lambda).body;
}

bool is_lambda(LispObjRef obj) {
	return (obj->which() == LAMBDA);
}

}
