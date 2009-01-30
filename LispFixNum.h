
#ifndef LISP_FIXNUM_H_INCLUDED
#define LISP_FIXNUM_H_INCLUDED

namespace Lisp
{
struct Fixnum : public struct LispObj
{
	void make(FixnumType v)
	{
		setType(eFixnumObj);
		object.resize(1);
		object[0] = v;
	}

	FixnumType value() {
		return object[0];
	}
};
			

}

#endif
