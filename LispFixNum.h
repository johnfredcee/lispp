
#ifndef LISP_FIXNUM_H_INCLUDED
#define LISP_FIXNUM_H_INCLUDED

namespace Lisp
{
	LispObjRef make_fixnum(CFixnum val);
	bool       is_fixnum(LispObjRef obj); 
}

#endif
