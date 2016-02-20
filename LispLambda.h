#if !defined(H_LISPLAMBDA)
#define H_LISPLAMBDA


namespace Lisp
{

LispObjRef make_lambda(LispObjRef args, LispObjRef bodt);
LispObjRef args(LispObjRef lambda);
LispObjRef body(LispObjRef lambda);
bool	   is_lambda(LispObjRef obj);

}

#endif



