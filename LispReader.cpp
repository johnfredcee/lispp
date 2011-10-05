
#include <cctype>
#include "LispNil.h"
#include "LispFixNum.h"
#include "LispString.h"
#include "LispSymbol.h"
#include "LispReader.h"
#include "LispCons.h"
#include "LispSymbol.h"

using namespace std;


namespace Lisp {
	Reader::Reader(std::istream& input) :  tokenType_(UNKNOWN), input_(input)  {
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
			ic = input_.get();
		}
		return result;
	}

	void Reader::nextToken() {
		char ic;
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
			tokenType_ = TERMINAL;
	}

	LispObjRef Reader::read() {
		nextToken();
		if (tokenType_ == TERMINAL) {
			return nil;
		}
		if (tokenType_ == NUMBER) {
			return make_fixnum(atoi(token_.c_str()));
		}		
		if (tokenType_ == RPAREN) {
			return nil;
		}
		if (tokenType_ == LPAREN) {
			return make_cons(read(), read());
		}
		if (tokenType_ == SYMBOL) {
			if (token_ == std::string("NIL")) {
				return nil;
			} else {
				return make_symbol(token_.c_str());
			}
		}
		if (tokenType_ == STRING) {
			return make_string(token_.c_str());
		}
		return nil;
	}

	LispObjRef Reader::operator()() {
		return read();
	}

	Reader::~Reader() {
	}
}

