#if !defined(H_LISPCONS)
#define H_LISPCONS


namespace Lisp
{

LispObjRef make_cons(LispObjRef car, LispObjRef cdr);
LispObjRef car(LispObjRef cons);
LispObjRef cdr(LispObjRef cons);
LispObjRef cadr(LispObjRef cons);
LispObjRef cddr(LispObjRef cons);
bool	   is_cons(LispObjRef obj);

}

#endif

