
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <cassert>

#include "LispObj.h"
#include "LispNil.h"
#include "LispReader.h"
#include "LispEval.h"
#include "LispPrinter.h"

using namespace Lisp;


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
	Lisp::Eval    eval;
	Lisp::Printer print(outstream.is_open() ? outstream : std::cout);

	boost::log::add_file_log("lispp.log");

    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	// REPL
	while ((!instream.is_open()) || (instream.is_open() && (instream.good()))) {
		LispObjRef obj = read();
//		print(obj);
		LispObjRef eobj = eval(obj, LispEnv::globalEnv);
		print(eobj);				
	}
	exit(0);
}
