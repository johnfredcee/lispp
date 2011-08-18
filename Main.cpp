
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

	// REPL
	while (1) {
		LispObjRef obj = read();
		LispObjRef eobj = eval(obj, LispEnv::globalEnv);
		print(eobj);
	}
	exit(0);
}
