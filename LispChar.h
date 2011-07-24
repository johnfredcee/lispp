#ifndef LISPCHAR_H
#define LISPCHAR_H

namespace Lisp
{
	LispObjRef make_char(u8 val);
	bool       is_char(LispObjRef obj); 
}

#endif
