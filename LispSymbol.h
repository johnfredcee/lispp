#if !defined(LISP_SYMBOL_H_INCLUDED)
#define LISP_SYMBOL_H_INCLUDED


namespace Lisp
{
	LispObjRef make_symbol(const char* symbol);
	bool       is_symbol(LispObjRef obj);
}

#endif
