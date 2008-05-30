#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

class Scanner
{
	public:
		
		enum eSymbolType
		{
			eBrace = 0,
			eString,
			eNumber,
			eSymbol,
			eSpecial,
			eSpace,
			eEndOfFile
		};
		
		
		enum eScannerState
		{
			eInWhiteSpace = 0,
			eInString,
			eInNumeric,
			eInSymbol,
			eInOpenBrace,
			eInCloseBrace,
			eFinished
		};

		Scanner(std::istream& in);
		
		std::string next(eSymbolType& kind);


		
	private:
		bool isSpecial(std::string symbol);
		
		static const char *specials[];
		
		std::istream& in_;
		eScannerState state_;
};

#endif
