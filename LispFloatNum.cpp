
#include <cassert>

#include <list>
#include <vector>
#include <iostream>
#include <string>

#include "LispObj.h"
#include "LispEnv.h"
#include "LispFloatNum.h"


namespace Lisp {
	LispObjRef make_floatnum(CFloatnum  val)
	{
		return boost::shared_ptr<LispObj>(new LispObj(val));
	}

	bool is_floatnum(LispObjRef obj)
	{
		return (obj->which() == FLOATNUM);
	}	
}

