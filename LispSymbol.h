#if !defined(LISP_SYMBOL_H_INCLUDED)
#define LISP_SYMBOL_H_INCLUDED

namespace Lisp
{
class Symbol;

class Symbol : public Obj
{
	typedef Symbol* SymbolPtr;			
	typedef Symbol& SymbolRef;
			
public:

	// default constructor == gensym
	Symbol()
	{
		symbol_count++;
		std::ostringstream value_stream;
		value_stream.setf( std::ios::hex, std::ios::basefield );
		value_stream.width( 8 );
		value_stream.fill( '0' );
		value_stream << "Sym#" << std::ios::hex << this << " ";
		name_ = value_stream.str();
	}
			
	Symbol(const Symbol& other)
	{
		if (&other != this)
		{
			name_ = other.name_;
			plist_ = other.plist_;
			symbol_count++;
		}
	}

	virtual eObjectType getObjectType() const
	{
		return eSymbolObj;
	}

	virtual Symbol* create(void) const
	{
		SymbolPtr result = new Symbol();
		return result;
	}

	virtual Symbol* clone() const
	{
		SymbolPtr result = new Symbol(*this);
		return result;
	}

	void print(std::ostream& out) const
	{
		out << name_;
	}

// 	bool identify(std::string in) const
// 	{
// 	}
	

	StringValue name()
	{
		return name_;
	}

	void name(StringValue& name)
	{
		name_ = name;
	}			

	Cons::ConsRef plist()
	{
		return plist_;
	}

	void plist(Cons::ConsRef plist)
	{
		plist_ = plist;
	}
	
	bool operator==(const Obj* other)
	{
		bool result = false;

		// comparison of two symbols is only T if they are the same symbol
		if (other->getObjectType() == eSymbolObj)
			result = (other == this);
		return result;
	}
			
private:
	StringValue name_;
	Cons plist_;
	static FixnumValue symbol_count;
};
	
}

#endif

