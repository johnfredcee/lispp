#if !defined(H_LISPFLOAT)
#define H_LISPFLOAT

namespace Lisp
{
	
	class LispFloat;

	class LispFloat : public LispObj
	{
		public:

			typedef LispFloat* LispFloatPtr;
			typedef LispFloat& LispFloatRef;			

			LispFloat() : value_(0)
			{};
			
			LispFloat(const LispFloat& other)
			{
				if (this != &other)
					value_ = other.value_;
			};
			
			LispFloat& operator=(const LispFloat& other)
			{
				if (this != &other)
					value_ = other.value_;
				return *this;
			}
			
			virtual LispFloatRef clone() const
			{
				LispFloat* result = new LispFloat(*this);
				return *result;
			}
			
			virtual LispFloatRef create(void)
			{
				LispFloat *result = new LispFloat();
				return *result;
			}
			
			operator LispFloatValue()
			{
				return value_;
			}

			operator LispFixnumValue()
			{
				return static_cast<LispFixnumValue>(value_);
			}

			operator LispStringValue()
			{
				std::ostringstream value_stream;
				value_stream << value_;
				return value_stream.str();
			}

			LispFloat& operator=(LispFloatValue& fval)
			{
				value_ = fval;
				return *this;
			}
			
			LispFloat& operator=(LispFixnumValue& fixnum)
			{
				value_ = static_cast<LispFixnumValue>(fixnum);
				return *this;
			}
			
			LispFloat& operator=(LispStringValue &str)
			{
				std::istringstream value_stream(str);
				value_stream >> value_;
				return *this;
			}
				

			void getObjectType(LispObj::eLispObjectType& kind)
			{
				kind = LispObj::eFloatObj;
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
			LispFloatValue value_;
			
	};
	
}
#endif
