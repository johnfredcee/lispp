
#ifndef LISP_FIXNUM_H_INCLUDED
#define LISP_FIXNUM_H_INCLUDED

namespace Lisp
{

	struct Fixnum : public LispObj
	{
		void make(FixnumType v)
		{
			object.tag.setType(eFixnumObj);
			object.values.resize(1);
			object.values[0] = LispValue(v);
		}
		
		FixnumType value()
		{
			return object.values[0];
		}
	};
			
}

#endif
