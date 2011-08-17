

#include <cctype>
#include "LispNil.h"
#include "LispFixNum.h"
#include "LispPrinter.h"

using namespace std;

namespace Lisp {
	Printer::Printer(ostream& output) : output_(output) {
		
	}

	void Printer::print(LispObjRef obj) {
		LispObjectType kind = static_cast<LispObjectType>(obj->which());		
		switch (kind) {
			case NIL:
				output_ << "NIL";
				break;
			case FIXNUM:				
				output_ << (s32)(boost::get<FixnumType>(*obj));
				break;
			case FLOATNUM:
				output_ << (f32)(boost::get<FloatnumType>(*obj));
				break;
			case STRING:
				output_ << "\"" << (std::string)(boost::get<StringType>(*obj)) << "\""; 
				break;
			case SYMBOL:
				output_ << static_cast<LispSymbol>(boost::get<SymbolType>(*obj)).first;
				break;
			default:
				output_ << "#UNPRINTABLE#";
				break;				
		}
		output_ << endl;
	}
}

