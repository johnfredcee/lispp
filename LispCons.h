#if !defined(H_LISPCONS)
#define H_LISPCONS

namespace Lisp
{
	class LispCons;

	class LispCons : public LispObj
	{
		public:

			typedef LispCons* LispConsPtr;
			typedef LispCons& LispConsRef;			

			LispCons() :
				car_(LispNull()->clone()),
				cdr(LispNull()->clone())
			{
			}

			LispCons(LispObj& car) :
				car(car->clone()),
				cdr_(LispNull()->clone())
			{
				car_ = car->clone();
				cdr_ = LispNull();
			}

			LispCons(LispObj& car, LispObj& cdr) :
				car_(car->clone()),
				cdr_(cdr->clone())
			{
			}

			void car(const LispObjRef car) 
			{
				car_ = car->clone();
			}

			void cdr(const LispObjRef cdr)
			{
				cdr_ = cdr->clone();
			}
			
			const LispObjRef car() const
			{
				return car_;
			}
			
			LispObjRef car()
			{
				return car_;
			}

			const LispObjRef cdr() const
			{
				return cdr_;
			}
			
			LispObjRef cdr()
			{
				return cdr_;
			}
			
			LispCons(const LispCons& other)
			{
				if (this != &other)
				{
					car_ = other.car_;
					cdr_ = other.cdr_;
				}
			}
			
			LispCons& operator=(const LispCons& other)
			{
				if (this != &other)
				{
					car_ = other.car_;
					cdr_ = other.cdr_;
				}				
				return *this;
			}

			/** to do -- modify cloning semantics for reference counting ? **/
			LispConsRef clone() const
			{
				LispCons* result = new LispCons(*this);
				return *result;
			}

			LispConsRef create(void)
			{
				LispCons* result = new LispCons();
				return *result;
			}

			operator LispStringValue()
			{
				std::ostringstream value_stream;
				value_stream.setf( ios::hex, ios::basefield );
				value_stream.width( 8 );
				value_stream << "Cons# " << this << " " << car_ << " " cdr_;
				return value_stream.str();
			}

			operator bool()
			{
				return (car_ && cdr_);
			}
			
			void getObjectType(LispObj::eLispObjectType& kind)
			{
				kind = LispObj::eConsObj;
			}

			void print(std::ostream& out) const
			{
				out << static_cast<LispStringValue>(*this);
			}

			LispObjPtr read(std::istream& in)
			{
				// not sure?
			}
			
		private:
			LispObjRef car_;
			LispObjRef cdr_;
	}
}

#endif

