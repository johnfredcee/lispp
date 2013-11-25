
#include <cassert>

#include <list>
#include <vector>
#include <iostream>
#include <string>

#include "LispObj.h"
#include "LispFixNum.h"

namespace Lisp {
	LispObjRef make_fixnum(CFixnum val)
	{
		return boost::shared_ptr<LispObj>(new LispObj(FixnumType(val)));
	}

	bool is_fixnum(LispObjRef obj)
	{
		return (obj->which() == FIXNUM);
	}	
}

