#if !defined(H_LISPCONS)
#define H_LISPCONS

#include "LispNil.h"
#include <utility>

namespace Lisp
{

struct Cons : public LispObj
{

	void make(PointerType car, PointerType cdr)
	{
		object.tag.setType(eConsObj);
		object.resize(2);
		object[0] = car;
		object[1] = cdr;
	}
	
	PointerType car()
	{
		return object[0];
	}

	
	PointerType cdr()
	{
		return object[1];
	}
};


}

#endif

