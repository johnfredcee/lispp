
#include <cassert>

#include <string>
#include <list>
#include <vector>
#include <ios>
#include <iostream>
#include <sstream>

#include "LispObj.h"
#include "LispNil.h"
#include "LispSymbol.h"

namespace Lisp {

LispObjRef make_symbol(const char* string) 
{
	std::string tempstr(string);
	LispSymbol sym(tempstr, nil);
	return boost::shared_ptr<LispObj>(new LispObj(SymbolType(sym)));
}


LispObjRef set_symbol_val(LispObjRef sym, LispObjRef rhs)
{
	SymbolType& symref = boost::get<SymbolType>(*sym);
	static_cast<LispSymbol>(symref).value = rhs;
	return static_cast<LispSymbol>(symref).value;
}

LispObjRef get_symbol_value(LispObjRef sym)
{
	assert(is_symbol(sym));
	return get_ctype<SymbolType>(sym).value;
}


bool is_symbol(LispObjRef obj) 
{
	return (obj->which() == SYMBOL);
}

bool is_quote_symbol(LispObjRef obj)
{
	return ((is_symbol(obj)) && (get_ctype<SymbolType>(obj).name == "QUOTE"));
}

} // namespace Lisp
