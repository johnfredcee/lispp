
#include <cassert>

#include <list>
#include <vector>
#include <iostream>
#include <string>

#include "LispObj.h"
#include "LispFixNum.h"

namespace Lisp {
	LispObjRef make_fixnum(const u32 val)
	{
		return boost::shared_ptr<LispObj>(new LispObj(val));
	}

	bool is_fixnum(LispObjRef obj)
	{
		return (obj->which() == FIXNUM);
	}	
}

