#if !defined(LISP_SYMBOL_H_INCLUDED)
#define LISP_SYMBOL_H_INCLUDED

namespace Lisp
{


struct Symbol : public LispObj
{
	void make(const CharType *symname)
	{
		int i = 0;

		object.setType(eSymbolObj);

		// calc length
		while (*symname != '\0')
		{
			++i;
			++symname;
		}

		// insert the pigs
		object.values.resize(i);
		symname = symname - i;
		i = 0;
		while(*symname != '\0')
		{
			object.values.push_back( LispValue( *symname ) );
			++i;
			++symname;
		}
	}

	std::size_t length() const
	{
		return object.values.size();
	}

	bool operator==(const Symbol& sym)
	{
		if (sym.length() == length())
		{
			bool result = true;			
			std::size_t i = 0;
			
			while ((i < length()) && result)
			{
				result = (
					CharType(sym.object.values[i]) ==
					CharType(object.values[i]) );
				i++;
			}
			return result;
		}
		return false;
	}
};

} // end namespace lisp


#endif
