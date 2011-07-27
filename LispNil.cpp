
#include <cassert>

#include <list>
#include <vector>
#include <iostream>
#include <string>

#include "LispObj.h"
#include "LispNil.h"


namespace Lisp
{
	LispObjRef nil = LispObjRef(new LispObj());

	bool is_nil(LispObjRef obj) {
		return (obj->which() == NIL);
	}

}
