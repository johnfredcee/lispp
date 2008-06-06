#if !defined(H_LISPFLOAT)
#define H_LISPFLOAT

namespace Lisp
{	

	class Floatnum : public Obj
	{
	public:

		typedef Floatnum* FloatnumPtr;
		typedef Floatnum& FloatnumRef;			

		Floatnum() : value_(0.0)
		{};
			
		Floatnum(const Floatnum& other)
		{
			if (this != &other)
				value_ = other.value_;
		};
		
		virtual eObjectType getObjectType() const
		{
			return eFloatnumObj;
		}

		virtual Floatnum* create(void) const
		{
			Floatnum *result = new Floatnum();
			return result;
		}

		virtual Floatnum* clone() const
		{
			Floatnum* result = new Floatnum(*this);
			return result;
		}
					   							
		void print(std::ostream& out) const
		{
			out << value_;
		}

		bool operator==(const Obj* other)
		{
			bool result = false;
			if (other->getObjectType() == eFloatnumObj)
				result = ( value_ == dynamic_cast<const Floatnum *>(other)->value_ );			
			return result;
		}
		
	private:
		FloatnumValue value_;
			
	};
	
}
#endif
