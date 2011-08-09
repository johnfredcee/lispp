#ifndef LISPREADER_H
#define LISPREADER_H

#include <iostream>
#include <string>
#include "LispObj.h"

namespace Lisp {
	class Reader {
	public:
		enum TokenType {
			UNKNOWN,
			LPAREN,
			SYMBOL,
			STRING,
			RPAREN,
			NUMBER,
			EOF
		};

		Reader(std::istream& input, std::ostream& output);

		virtual ~Reader();

		std::string readString();
		
		std::string readNumberOrSymbol(TokenType& type);

		void nextToken();

		LispObjRef read();

		std::string  token_;

		TokenType    tokenType_;

	private:
		std::istream& input_;
		std::ostream& output_;
		std::string  current_line_;
	};

}
#endif
