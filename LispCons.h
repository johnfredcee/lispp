#if !defined(H_LISPCONS)
#define H_LISPCONS

#include "LispNil.h"
#include <utility>

namespace Lisp
{

struct Cons : public LispObj
{

	void make(const PointerType& car, const PointerType& cdr)
	{
		object.tag.setType(eConsObj);
		object.values.resize(2);
		object.values[0] = LispValue(car);
		object.values[1] = LispValue(cdr);
	}
	
	PointerType car() const
	{
		return object.values[0];
	}

	
	PointerType cdr() const
	{
		return object.values[1];
	}
};


}

#endif

