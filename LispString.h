#if !defined(H_LISPSTRING)
#define H_LISPSTRING

namespace Lisp
{
	class String;

	class String : public Obj
	{
	public:

		typedef String* StringPtr;
		typedef String& StringRef;
		
		String() : value_("")
		{};

		String( const String& other )
		{
			if (this != &other)
				value_ = other.value_;
		}

		virtual eObjectType getObjectType() const
		{
			return eStringObj;
		}

		virtual String* create(void) const
		{
			StringPtr result = new String();
			return result;
		}

		virtual String* clone() const
		{
			StringPtr result = new String(*this);
		}

		void print(std::ostream& out) const
		{
			out << "\"" << value_ << "\"";
		}

		bool operator==(const Obj* other)
		{
			bool result = false;
			if (other->getObjectType() == eStringObj)
				result = ( value_ == dynamic_cast<const String*>(other)->value_ );
			return result;
		}
	private:
		StringValue value_;
	};
}

#endif
