#if !defined(LISP_SYMBOL_H_INCLUDED)
#define LISP_SYMBOL_H_INCLUDED

namespace Lisp
{


struct Symbol : public struct LispObj
{
	void make(const CharType *symname)
	{
		int i = 0;

		setType(eSymbolObj);

		// calc length
		while (*symname != '\0')
		{
			++i;
			++symname;
		}

		// insert the pigs
		object.resize(i+1);
		symname = symname - i;
		i = 0;
		while(*symname != '\0')
		{
			object[i] = *symname;
			++i;
			++symname;
		}
		object[i+1] = '\0';
	}

	CharType& operator[](std::size_t i) 
	{
		return object[i];
	}

	const CharType& operator[](std::size_t i) const
	{
		return object[i];
	}

	std::size_t length()
	{
		return object[i].size();
	}
};

} // end namespace lisp


#endif
