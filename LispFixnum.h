
#ifndef LISP_FIXNUM_H_INCLUDED
#define LISP_FIXNUM_H_INCLUDED

namespace Lisp
{
	
	class LispFixnum;

	class LispFixnum : public LispObj
	{
		public:

			typedef LispFixnum* LispFixnumPtr;
			typedef LispFixnum& LispFixnumRef;			

			LispFixnum() : value_(0)
			{};
			
			LispFixnum(const LispFixnum& other)
			{
				if (this != &other)
					value_ = other.value_;
			};
			
			LispFixnum& operator=(const LispFixnum& other)
			{
				if (this != &other)
					value_ = other.value_;
				return *this;
			}
			
			virtual LispFixnumRef clone() const
			{
				LispFixnumPtr result = new LispFixnum(*this);
				return result;
			}
			
			virtual LispFixnumRef create(void)
			{
				LispFixnumPtr result = new LispFixnum();
				return result;
			}
			
			operator LispFixnumValue()
			{
				return value_;
			}

			operator LispFloatValue()
			{
				return static_cast<LispFloatValue>(value_);
			}

			operator LispStringValue()
			{
				std::ostringstream value_stream;
				value_stream << value_;
				return value_stream.str();
			}
			
			LispFixnum& operator=(LispFixnumValue& fixnum)
			{
				value_ = fixnum;
				return *this;
			}
			
			LispFixnum& operator=(LispFloatValue& fval)
			{
				value_ = static_cast<LispFixnumValue>(fval);
				return *this;
			}

 			LispFixnum& operator=(LispStringValue &str)
			{
				std::istringstream value_stream(str);
				value_stream >> value_;
				return *this;
			}
					
									  
			void getObjectType(LispObj::eLispObjectType& kind)
			{
				kind = LispObj::eFixnumObj;
			}
			
			void print(std::ostream& out) const
			{
				out << value_;
			}

			LispObjPtr read(std::istream& in)
			{
				in >> value_;
			}

			
		private:
			LispFixnumValue value_;
			
	};

}

#endif
