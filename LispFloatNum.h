
#ifndef LISP_FIXNUM_H_INCLUDED
#define LISP_FIXNUM_H_INCLUDED

namespace Lisp
{
	LispObjRef make_floatnum(CFloatnum val);
	bool       is_floatnum(LispObjRef obj); 
}

#endif
