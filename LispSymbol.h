#if !defined(LISP_SYMBOL_H_INCLUDED)
#define LISP_SYMBOL_H_INCLUDED


namespace Lisp
{
	LispObjRef make_symbol(const char* symbol);
	LispObjRef get_symbol_value(LispObjRef sym);
	bool       is_symbol(LispObjRef obj);
	bool is_quote_symbol(LispObjRef obj);
}

#endif
