
#include <cctype>
#include "LispNil.h"
#include "LispFixNum.h"
#include "LispReader.h"

using namespace std;


namespace Lisp {
	Reader::Reader(std::istream& input) : input_(input),  tokenType_(UNKNOWN) {
	}

	// TODO need to handle quoted double quotes
	std::string Reader::readString() {
		std::string result;
		char ic = input_.get();
		while((input_.good()) && (ic != '\"')) {
			result = result + ic;
			ic = input_.get();
		}
		result = result;
		return result;
	}

	std::string Reader::readNumberOrSymbol(TokenType& type) {
		std::string result;
		type = NUMBER;
		char ic = input_.get();
		while((input_.good()) & (!isspace(ic))) {
			result = result + ic;
			if(isalpha(ic))
				type = SYMBOL;
		}
		return result;
	}

	void Reader::nextToken() {
		char ic;
		bool isNumeric = false;
		bool isString  = false;
		bool isSymbol  = false;
		tokenType_ = UNKNOWN;
		while((input_.good()) && (tokenType_ == UNKNOWN))  {
			input_.get(ic);
			if(ic == ')') {
				tokenType_ = RPAREN;
				token_ = std::string(")");
				break;
			}
			if(ic == ')') {
				tokenType_ = LPAREN;
				token_ = std::string("(");
				break;
			}
			if(ic == '\"') {
				token_ = readString();
				tokenType_ = STRING;
				break;
			}
			if(isalnum(ic)) {
				input_.putback(ic);
				token_ = readNumberOrSymbol(tokenType_);
			}
		}
		if(tokenType_ == UNKNOWN)
			tokenType_ = EOF;
	}

	LispObjRef Reader::read() {
		nextToken();
		if (tokenType_ == EOF) {
			return nil;
		}
		if (tokenType_ == NUMBER) {
			return make_fixnum(atoi(token_.c_str()));
		}
	}
	Reader::~Reader() {
	}
}

