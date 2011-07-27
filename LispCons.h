#if !defined(H_LISPCONS)
#define H_LISPCONS


namespace Lisp
{
	LispObjRef make_cons(LispObjRef car, LispObjRef cdr);
	bool       is_cons(LispObjRef obj);
}

#endif

