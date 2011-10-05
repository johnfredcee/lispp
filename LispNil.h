#if !defined(H_LISPNIL)
#define H_LISPNIL

#include "LispObj.h"

namespace Lisp
{
    // the singulariy is here!
	extern LispObjRef nil;
    extern bool is_nil(LispObjRef obj);

}


#endif
