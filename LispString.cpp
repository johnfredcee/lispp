
#include <cassert>

#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "LispObj.h"
#include "LispString.h"

namespace Lisp
{
	LispObjRef make_string(const char* str)
	{
		std::string tempstr(str);
		return boost::shared_ptr<LispObj>(new LispObj(tempstr));
	}
	
	bool is_string(LispObjRef obj) 
	{
		return (obj->which() == STRING);
	}
}

