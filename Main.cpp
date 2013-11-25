
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

void trace(LispObjRef obj)
{
	switch(obj->which())
	{
		case NIL:
			BOOST_LOG_TRIVIAL(trace) << " NIL";
			break;
		case	CHAR:
			BOOST_LOG_TRIVIAL(trace) << " char=" << get_ctype<CharType>(obj);
			break;
		case	FIXNUM:
			BOOST_LOG_TRIVIAL(trace) << " char=" << get_ctype<FixnumType>(obj);
			break;
		case	FLOATNUM:
			BOOST_LOG_TRIVIAL(trace) << " char=" << get_ctype<FloatnumType>(obj);
			break;
		case	SYMBOL:
			BOOST_LOG_TRIVIAL(trace) << " sym=" << get_ctype<SymbolType>(obj).first;
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
	}
		
}

int main(int argc, char** argv)
{
	std::ifstream instream;

	instream.open("autoexec.lisp", std::ifstream::in); 
	Lisp::Reader  read(instream);
	Lisp::Eval    eval;
	Lisp::Printer print(std::cout);

	boost::log::add_file_log("lispp.log");


	// REPL
	while (instream.good()) {
		LispObjRef obj = read();
		trace(obj);
//		LispObjRef eobj = eval(obj, LispEnv::globalEnv);
//		print(eobj);
	}
	exit(0);
}
