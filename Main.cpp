
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
	Lisp::Reader  read(std::cin);
	Lisp::Eval    eval;
	Lisp::Printer print(std::cout);

	boost::log::add_file_log("lispp.log");

    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	// REPL
	while (1) {
		LispObjRef obj = read();
//		print(obj);
		LispObjRef eobj = eval(obj, LispEnv::globalEnv);
		print(eobj);
	}
	exit(0);
}
