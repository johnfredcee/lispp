
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
	std::pair<std::string, LispObjRef> sym(tempstr, nil);
	return boost::shared_ptr<LispObj>(new LispObj(SymbolType(sym)));
}


LispObjRef set_symbol_val(LispObjRef sym, LispObjRef rhs)
{
	SymbolType& symref = boost::get<SymbolType>(*sym);
	static_cast<LispSymbol>(symref).second = rhs;
	return static_cast<LispSymbol>(symref).second;
}

LispObjRef get_symbol_val(LispObjRef sym)
{
	return get_ctype<SymbolType>(sym).second;
}

bool is_symbol(LispObjRef obj) 
{
	return (obj->which() == SYMBOL);
}

bool is_quote_symbol(LispObjRef obj)
{
	return ((is_symbol(obj)) && (get_ctype<SymbolType>(obj).first == "QUOTE"));
}

} // namespace Lisp
