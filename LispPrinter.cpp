

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

	void Printer::print_cons(LispObjRef obj) {
		print(car(obj));
		LispObjRef next(cdr(obj));
		if (!is_cons(next)) {
			output_ << " ";
			print_cons(next);					
			return;
		}
		if (is_nil(next)) {
			return;
		}
		output_ << " . ";
		print(next);
	}

	void Printer::print(LispObjRef obj) {
		if (is_nil(obj))
			output_ << "NIL";
		else if (is_fixnum(obj))
			output_ << get_ctype<FixnumType>(obj); // (CFixnum)(boost::get<FixnumType>(*obj));
		else if (is_floatnum(obj))
			output_ <<  get_ctype<FloatnumType>(obj); //(CFloatnum)(boost::get<FloatnumType>(*obj));
		else if (is_string(obj))
			output_ << "\"" << get_ctype<StringType>(obj) << "\""; // ""(CString)(boost::get<StringType>(*obj)) << "\""; 
		else if (is_symbol(obj))
			output_ << get_ctype<SymbolType>(obj).first; // static_cast<LispSymbol>(boost::get<SymbolType>(*obj)).first;
		else if (is_cons(obj)) {
			output_ << "(";
			print_cons(obj);
			output_ << ")";			
		}
		else
			output_ << "#UNPRINTABLE#";
	}

	void Printer::operator()(LispObjRef obj) {
		print(obj);
		output_ << endl;
	}
}

