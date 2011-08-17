#ifndef LISPPRINTER_H
#define LISPPRINTER_H

#include <iostream>
#include <string>
#include "LispObj.h"

namespace Lisp
{
	class Printer {
		Printer(std::ostream& output);
		void print(LispObjRef obj);
	private:
		std::ostream& output_;

	};
}

#endif
