#if !defined(H_LISPSTRING)
#define H_LISPSTRING

namespace Lisp
{
	class String;

	class String : public LispObj
	{
	public:
		void make(const CharType *value)
		{
			int i = 0;
			
			object.setType(eStringObj);
			
			// calc length
			while (*value != '\0')
			{
				++i;
				++value;
			}
			
			// insert the pigs (string manipulation will not be this things forte)
			object.values.resize(i);
			value = value - i;
			i = 0;
			while(*value != '\0')
			{
				object.values.push_back( LispValue( *value ) );
				++i;
				++value;
			}
		}

		std::size_t length() const
		{
			return object.values.size();
		}
		
		bool operator==(const String& str)
		{
			if (str.length() == length())
			{
				bool result = true;			
				std::size_t i = 0;
				
				while ((i < length()) && result)
				{
					result = (
						CharType(str.object.values[i]) ==
						CharType(object.values[i]) );
					i++;
				}
				return result;
			}
			return false;
		}
	};
}

#endif
