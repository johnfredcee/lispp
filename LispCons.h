#if !defined(H_LISPCONS)
#define H_LISPCONS

#include "LispNil.h"
#include <utility>

namespace Lisp
{
	class Cons;

	class Cons : public Obj
	{
	public:

		typedef Cons* ConsPtr;
		typedef Cons& ConsRef;			

		Cons() :
			value_(NIL::make(), NIL::make())
		{
		}

		Cons(const Cons& other) 
		{
			if (this != &other)
				value_ = other.value_;
		}

		Obj::eObjectType Cons::getObjectType() const
		{
			return Obj::eConsObj;
		}

		
		Cons* make() const
		{
			return new Cons();
		}
		
		Cons* create() const
		{
			return new Cons();
		}
		
		
		Cons* clone() const
		{
			return new Cons(*this);
		}

		virtual void print(std::ostream& out) const
		{
			out << " ";
			value_.first->print(out);
			out << " . ";
			value_.second->print(out);
			out << " ";
		}

		bool operator==(const Obj* other)
		{
			bool result = false;
			if (other->getObjectType() == eConsObj)
				result = ( ( value_.first == dynamic_cast<const Cons*>(other)->value_.first ) &&
						   ( value_.second == dynamic_cast<const Cons*>(other)->value_.second ) );
			return result;
		}

		Obj* car()
		{
			return value_.first;
		}

		Obj* cdr()
		{
			return value_.second;
		}
			
	private:
		
		std::pair<Obj*, Obj*> value_;
	};
}

#endif

