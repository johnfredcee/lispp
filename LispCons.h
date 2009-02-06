#if !defined(H_LISPCONS)
#define H_LISPCONS

#include "LispNil.h"
#include <utility>

namespace Lisp
{

struct Cons : public struct LispObj
{

	void make(PointerType car, PointerType cdr)
	{
		setType(eConsObj);
		object_.resize(2);
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

