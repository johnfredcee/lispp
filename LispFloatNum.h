
#ifndef LISP_FLOATNUM_H_INCLUDED
#define LISP_FLOATNUM_H_INCLUDED

namespace Lisp
{
	LispObjRef make_floatnum(CFloatnum val);
	bool       is_floatnum(LispObjRef obj); 
}

#endif
