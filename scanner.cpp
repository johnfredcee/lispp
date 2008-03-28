
#include <string>
#include <cctype>
#include <ios>
#include <iostream>

#include "scanner.h"

const char *Scanner::specials[] = { "let", "flet", "lambda", "cond" };

Scanner::Scanner(std::istream& in)	:
	in_(in),
	state_(eInWhiteSpace)
{};

bool Scanner::isSpecial(std::string symbol)
{
	bool result = false;
	for(int i = 0; i < sizeof(specials) / sizeof(const char *); i++)
	{
		result = result || (symbol == std::string(Scanner::specials[i]));
	}
	return result;
}

std::string Scanner::next(Scanner::eSymbolType& kind)
{
	std::string result("");
			
	switch (state_)
	{
		case eInWhiteSpace:
		{
			char c;
			bool isSpace = true;
					
			do {
				if (std::isspace(in_.peek())) {
					in_.get(c);
					result += c;
				}
				else
					isSpace = false;

			} while (isSpace);
					
			kind = eSpace;
					
			c = in_.peek();
			if (in_.eof())
				state_ = eFinished;
			if (c == ')')
				state_ = eInCloseBrace;
			if (c == '(')
				state_ = eInOpenBrace;
			if (c == '"')
				state_ = eInString;
			if (std::isdigit(c))
				state_ = eInNumeric;
			if (std::isalpha(c))
				state_ = eInSymbol;
					
		}

		case eInCloseBrace:
		case eInOpenBrace:
		{
			char c;
					
			in_.get(c);
			result += c;
			kind = eBrace;					
			state_ = eInWhiteSpace;
		}

		case eInString:
		{
			char c;
			bool isString = true;
					
			do {
				if ((!in_.eof()) && (in_.peek() != '"')) {
					/* the next character is escaped */
					in_.get(c);
					if (c == '\\') 
						in_.get(c);
					result += c;
				}
				else
					isString = false;

			} while (isString);

			kind = eString;
					
			state_ = eInWhiteSpace;
		}
				
		case eInNumeric:
		{
			char c;
			bool isNumeric = true;
					
			do {
				if (std::isxdigit(in_.peek())) {
					in_.get(c);
					result += c;
				}
				else
					isNumeric = false;

			} while (isNumeric);

			kind = eNumber;
					
			state_ = eInWhiteSpace;
		}

		case eInSymbol:
		{
			char c;
			bool isSymbolic = true;
					
			do {
				if (std::isalnum(in_.peek())) {
					in_.get(c);
					result += c;
				}
				else
					isSymbolic = false;

			} while (isSymbolic);

			kind = isSpecial(result) ? eSpecial : eSymbol;
					
			state_ = eInWhiteSpace;
		}
	}
			
	return result;
				
}
		
