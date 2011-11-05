#ifndef LISPPRINTER_H
#define LISPPRINTER_H

#include <iostream>
#include <string>
#include "LispObj.h"

namespace Lisp
{
	class Printer {
	public:
		Printer(std::ostream& output);
		void print_cons(LispObjRef cons);
		void print(LispObjRef obj);
		void operator()(LispObjRef obj);
	private:
		std::ostream& output_;

	};
}


#endif
