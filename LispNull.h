#if !defined(H_LISPNULL)
#define H_LISPNULL

namespace Lisp
{
	class LispNull;
	{
	public:
		typedef LispNull& LispNullRef;
		
		LispNull()
		{
		}

		LispNull(const LispNull& other)
		{
		}

		LispNull& operator=(const LispNull &other)
		{
			return *this;
		}

		operator bool()
		{
			return false;
		}

		LispNullRef create()
		{
			LispNull *result = new LispNull();
			return *result;
		}

		LispNullRef clone()
		{
			LispNull *result = new LispNull(*this);
			return *result;			
		}

		void getObjectType(LispObj::eLispObjectType& kind)
		{
			kind = LispObj::eNullObj;
		}

		void print(std::ostream& out) const
		{
			out << " NIL ";
		}
		
		LispObjPtr read(std::istream& in)
		{
			// not sure?
		}
		
	};
}
#endif

