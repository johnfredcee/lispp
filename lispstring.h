#if !defined(H_LISPSTRING)
#define H_LISPSTRING

namespace Lisp
{
	class LispString;
	class LispString : public LispObj
	{
		public:
			typedef LispString* LispStringPtr;

			LispString() : value_("")
			{}
			
			LispString(const LispString& other)
			{
				if (this != &other)
					value_ = other.value_;
			};
			
			LispString& operator=(const LispString& other)
			{
				if (this != &other)
					value_ = other.value_;
				return *this;
			}
			
			virtual LispStringRef clone() const
			{
				LispString* result = LispString(*this);
				return *result;
			}
			
			virtual LispStringRef create(void)
			{
				LispString *result = new LispString();
				return *result;
			}

			operator LispStringValue()
			{
				return value_;
			}
			
			operator LispFloatValue()
			{
				LispFloatValue result = 0.0;

				std::itringstream value_stream(value_);
				value_stream >> result;
				return result;
			}

			operator LispFixnumValue()
			{
				LispFixnumValue result = 0.0;

				std::itringstream value_stream(value_);
				value_stream >> result;
				return result;
			}

			
			LispString& operator=(LispStringValue& sval)
			{
				value_ = sval;
				return *this;
			}
			
			
			LispString& operator=(LispFloatValue& fval)
			{
				std::ostringstream value_stream;
				value_stream << fval;
				value_ = value_stream.str();
				return *this;
			}
			
			LispString& operator=(LispFixnumValue& fixnum)
			{
				std::ostringstream value_stream;
				value_stream << fixnum;
				value_ = value_stream.str();
				return *this;
			}
			
			void getObjectType(LispObj::eLispObjectType& kind)
			{
				kind = LispObj::eStringObj;
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
			LispStringValue value_;
	};
}
#endif

