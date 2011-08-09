#if !defined(H_LISPSTRING)
#define H_LISPSTRING

namespace Lisp
{
	LispObjRef make_string(const char* string);
	bool       is_string(LispObjRef obj);
}

#endif
