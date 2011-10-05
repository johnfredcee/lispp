
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
		SymbolType& symref = boost::get<SymbolType>(*sym);
		return static_cast<LispSymbol>(symref).second;
	}

	bool is_symbol(LispObjRef obj) 
	{
		return (obj->which() == SYMBOL);
	}
	
}
