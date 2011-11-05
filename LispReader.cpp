
#include <cctype>
#include "LispNil.h"
#include "LispFixNum.h"
#include "LispFloatNum.h"
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
	type = FIXNUM;
	char ic = input_.get();
	if (isalpha(ic))
		type = SYMBOL;
	while((input_.good()) & (!isspace(ic))) {
		result = result + ic;
		if ((type == FIXNUM) && (ic == '.')) {
			type = FLOATNUM;
		}
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

LispObjRef Reader::readToken() {
	nextToken();
	if (tokenType_ == TERMINAL) {
		return nil;
	}
	if (tokenType_ == FIXNUM) {
		return make_fixnum(atoi(token_.c_str()));
	}		
	if (tokenType_ == FLOATNUM) {
		return make_floatnum(atof(token_.c_str()));
	}
	if (tokenType_ == RPAREN) {
		return nil;
	}
	if (tokenType_ == LPAREN) {
		return nil;
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

LispObjRef Reader::read_the_rest()
{
	LispObjRef cdr = readToken();
	if (tokenType_ == RPAREN)
		return nil;
	if (tokenType_ == LPAREN)
		cdr = read_list();
	return make_cons(cdr, read_the_rest());
}

LispObjRef Reader::read_list() 
{
	LispObjRef car = readToken();
	if (tokenType_ == LPAREN)
		car = read_list();
	if (tokenType_ != RPAREN)
		return make_cons(car, read_the_rest());
	return make_cons(car, nil);
}

LispObjRef Reader::read() {
	LispObjRef first = readToken();
	if (tokenType_ != LPAREN)
		return first;
	return
		read_list();
}

LispObjRef Reader::operator()() {
	return read();
}

Reader::~Reader() {
}
}

