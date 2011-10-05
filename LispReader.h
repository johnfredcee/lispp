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
			TERMINAL
		};

		Reader(std::istream& input);

		virtual ~Reader();

		std::string readString();
		
		std::string readNumberOrSymbol(TokenType& type);

		void nextToken();

		LispObjRef readToken();

		LispObjRef read_the_rest();

		LispObjRef read_list();

		LispObjRef read();

		LispObjRef operator()();


		std::string  token_;

		TokenType    tokenType_;

	private:
		std::istream& input_;
		std::string  current_line_;
	};

}
#endif
