
#include <cassert>

#include <list>
#include <vector>
#include <iostream>
#include <string>

#include "LispObj.h"
#include "LispFixNum.h"

namespace Lisp {
	LispObjRef make_char(const u8 val)
	{
		return boost::shared_ptr<LispObj>(new LispObj(CharType(val)));
	}

	bool is_char(LispObjRef obj)
	{
		return (obj->which() == CHAR);
	}	
}
