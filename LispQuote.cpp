
#include "LispObj.h"
#include "LispQuote.h"

namespace Lisp {

LispObjRef LispQuote::quote_fn(LispObjRef cons) {
	return cons;		
}

}
