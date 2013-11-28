#include "LispObj.h"
#include "LispPrimitive.h"

namespace Lisp {

bool is_primitive(LispObjRef obj) {
	return (obj->which() == PRIM);
}

}
