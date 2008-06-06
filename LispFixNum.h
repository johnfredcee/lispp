
#ifndef LISP_FIXNUM_H_INCLUDED
#define LISP_FIXNUM_H_INCLUDED

namespace Lisp
{
	
	class Fixnum;

	class Fixnum : public Obj
	{
	public:

		typedef Fixnum* FixnumPtr;
		typedef Fixnum& FixnumRef;			

		Fixnum() : value_(0)
		{};
			
		Fixnum(const Fixnum& other)
		{
			if (this != &other)
				value_ = other.value_;
		};

		virtual eObjectType getObjectType() const
		{
			return eFixnumObj;
		}
		
		virtual Fixnum* create(void) const
		{
			FixnumPtr result = new Fixnum();
			return result;
		}

		virtual Fixnum* clone() const
		{
			FixnumPtr result = new Fixnum(*this);
			return result;
		}
														  			
		void print(std::ostream& out) const
		{
			out << value_;
		}

// 			bool identify(std::string in) const
// 			{
// 				in >> value_;
// 			}

		bool operator==(const Obj* other)
		{
			bool result = false;
			if (other->getObjectType() == eFixnumObj)
				result = ( value_ == dynamic_cast<const Fixnum*>(other)->value_ );
			return result;
		}
	private:
		FixnumValue value_;
			
	};

}

#endif
