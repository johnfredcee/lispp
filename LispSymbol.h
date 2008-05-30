#if !defined(H_LISPSYMBOL)
#define H_LISPSYMBOL

namespace Lisp
{
	class LispSymbol;

	class LispSymbol : public LispObj
	{
			typedef LispSymbol& LispSymbolPtr;			
			typedef LispSymbol& LispSymbolRef;
			
		public:
			LispSymbol()
			{
				symbol_count++;
				std::ostringstream value_stream;
				value_stream.setf( ios::hex, ios::basefield );
				value_stream.width( 8 );
				value_stream.fill( '0' );
				value_stream << "Sym#" << ios::hex() << this << " " << car_ << " " cdr_;
				name_ = value_stream.str();
			}
			
			LispSymbol(LispStringValue& name) : name_(name)
			{
				symbol_count++;
			}

			LispSymbol(LispStringValue& name, LispObj& obj)
			{
				plist->car(obj);
			}

			LispSymbol(LispSymbol& other)
			{
				if (&other != this)
				{
					name_ = other->name_;
					plist_ = other->plist_;
					symbol_count++;
				}
			}

			LispSymbol& operator=(LispSymbol& other)
			{
				if (&other != this)
				{
					name_ = other->name_;
					plist_ = other->plist_;
					symbol_count++;
				}
				return *this;
			}
			
			operator LispObjRef()
			{
				return plist->car();
			}

			LispObjRef plist()
			{
				return plist->cdr();
			}

			LispSymbolRef operator=(LispObjRef& val)
			{
				plist->car(val);
			}

			operator LispStringVal()
			{
				return name_;
			}
			
			void getObjectType(LispObj::eLispObjectType& kind)
			{
				kind = LispObj::eSymbolObj;
			}
			
		private:
			LispStringValue name_;
			LispCons plist_;
			static LispFixnumValue symbol_count;
	}
	
}

#endif

