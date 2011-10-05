

#include <cctype>
#include "LispNil.h"
#include "LispFixNum.h"
#include "LispFloatNum.h"
#include "LispString.h"
#include "LispSymbol.h"
#include "LispReader.h"
#include "LispCons.h"
#include "LispPrinter.h"

using namespace std;

namespace Lisp {
	Printer::Printer(ostream& output) : output_(output) {
		
	}

	void Printer::print(LispObjRef obj) {
		if (is_nil(obj))
			output_ << "NIL";
		else if (is_fixnum(obj))
			output_ << (CFixnum)(boost::get<FixnumType>(*obj));
		else if (is_floatnum(obj))
			output_ << (CFloatnum)(boost::get<FloatnumType>(*obj));
		else if (is_string(obj))
			output_ << "\"" << (CString)(boost::get<StringType>(*obj)) << "\""; 
		else if (is_symbol(obj))
			output_ << static_cast<LispSymbol>(boost::get<SymbolType>(*obj)).first;
		else if (is_cons(obj)) {
			output_ << "(";
			LispObjRef next(cdr(obj));
			if (!is_nil(next))
				print(next);
			else
				output_ << ")";			
		}
		else
			output_ << "#UNPRINTABLE#";
		output_ << endl;
	}

	void Printer::operator()(LispObjRef obj) {
		print(obj);
	}
}

