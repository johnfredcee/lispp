#ifndef LISPQUOTE_H
#define LISPQUOTE_H

#include "LispObj.h"
#include "LispEnv.h"

namespace Lisp {

  class LispQuote {
  public:
	static LispObjRef quote_fn(LispObjRef cons, LispEnvRef env);
  };


}
#endif
