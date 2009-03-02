#if !defined(H_LISPFLOAT)
#define H_LISPFLOAT

namespace Lisp
{	

	struct Floatnum : public LispObj
	{
		void make(FloatnumType v)
		{
			object.tag.setType(eFloatnumObj);
			object.values.resize(1);
			object.values[0] = LispValue(v);
		}

		FloatnumType value()
		{
			return object.values[0];
		}
				
	};
	
}
#endif
