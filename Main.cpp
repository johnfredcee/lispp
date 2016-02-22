
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <fstream>
#include <cassert>

#include "LispObj.h"
#include "LispNil.h"
#include "LispCons.h"
#include "LispReader.h"
#include "LispEval.h"
#include "LispPrinter.h"

using namespace Lisp;

namespace Lisp
{
Lisp::Eval eval;
}


// exists to be invoked from gdb for debugging purposes
void trace(LispObjRef obj)
{
	BOOST_LOG_TRIVIAL(trace) << "--";
	switch(obj->which())
	{
		case NIL:
			BOOST_LOG_TRIVIAL(trace) << " NIL";
			break;
		case	CHAR:
			BOOST_LOG_TRIVIAL(trace) << " char=" << get_ctype<CharType>(obj);
			break;
		case	FIXNUM:
			BOOST_LOG_TRIVIAL(trace) << " fixnum=" << get_ctype<FixnumType>(obj);
			break;
		case	FLOATNUM:
			BOOST_LOG_TRIVIAL(trace) << " floatnum=" << get_ctype<FloatnumType>(obj);
			break;
		case	SYMBOL:
			BOOST_LOG_TRIVIAL(trace) << " sym=" << get_ctype<SymbolType>(obj).name;
			break;
		case	STRING:
			BOOST_LOG_TRIVIAL(trace) << " char=" << get_ctype<StringType>(obj);
			break;
		case	CONS:
			BOOST_LOG_TRIVIAL(trace) << " car="; trace(car(obj));
			BOOST_LOG_TRIVIAL(trace) << " cdr="; trace(cdr(obj));
			break;
		case	PRIM:
			BOOST_LOG_TRIVIAL(trace) << " prim() ";
			break;
		case	LAMBDA:
			BOOST_LOG_TRIVIAL(trace) << " lambda() ";
			BOOST_LOG_TRIVIAL(trace) << " == args() == ";
			trace(get_ctype<LambdaType>(obj).args);
			BOOST_LOG_TRIVIAL(trace) << " == body() == ";			
			trace(get_ctype<LambdaType>(obj).body);				  
			break;			
	}
	BOOST_LOG_TRIVIAL(trace) << "--";
}

int main(int argc, char** argv)
{
	std::ifstream instream;

	if (argc > 1) {
		instream.open(argv[1], std::ifstream::in);
	}

	std::ofstream outstream;
	if (argc > 2) {
		outstream.open(argv[2], std::ofstream::out); 
	}
		
	Lisp::Reader  read(instream.is_open() ? instream : std::cin);
	Lisp::Printer print(outstream.is_open() ? outstream : std::cout);

	// REPL
	while ((!instream.is_open()) || (instream.is_open() && (instream.good()))) {
		LispObjRef obj = read();
		printf("Read as :");
		print(obj);
		LispObjRef eobj = eval(obj, LispEnv::globalEnv);
		printf("Result is :");		
		print(eobj);				
	}
	exit(0);
}
