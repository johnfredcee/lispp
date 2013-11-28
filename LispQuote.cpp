
#include "LispObj.h"
#include "LispEnv.h"
#include "LispQuote.h"
#include "LispCons.h"

namespace Lisp {

  LispObjRef LispQuote::quote_fn(LispObjRef cons, LispEnvRef env) {
	  return cons;		
  }

}
