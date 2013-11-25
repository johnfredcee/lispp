
#include <boost/log/trivial.hpp>
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

std::string Reader::readString() {
	std::string result;
	char ic = input_.get();
	while ((input_.good()) && (ic != '\"')) 
	{
		if (ic != '\\') 
		{
			result = result + ic;			
		}
		else 
		{
			ic = input_.get();
			result = result + ic;
		}
		ic = input_.get();
	}
	result = result;
	return result;
}

char hexval(char c) 
{
	if ((c >= '0') && (c <= '9'))
		return c - '0';
	if ((c >= 'A') && (c <= 'F'))
		return c - 'A';
	if ((c >= 'a') && (c <= 'f'))
		return c - 'a';
	return 0;
 }

// char literals 
// either #\c - literal char c
// or     #8F - hex code 8F
std::string Reader::readChar()
{

	std::string result;
	
	char ic = input_.get();
	if (!input_.good())
		result = "";
	else {
		if (ic == '\\')
			result += input_.get();
		else {
			char val = hexval(ic) * 16;
			ic = input_.get();
			if (input_.good()) {
				val += hexval(ic);
			}			
			result += val;
		}
	}
	return result;
}

std::string Reader::readNumberOrSymbol(TokenType& type) {
	std::string result;
	type = FIXNUM;
	char ic = input_.get();
	if (isalpha(ic))
		type = SYMBOL;
	while((input_.good()) & (!isspace(ic)) && (ic!=')') && (ic!='(')) {
		result = result + ic;
		if ((type == FIXNUM) && (ic == '.')) {
			type = FLOATNUM;
		}
		ic = input_.get();
	}
	// if it was lexically important, stick it back
	if (!isspace(ic))
		input_.putback(ic);
	return result;
}

std::string Reader::readQuote(TokenType& type) {
	std::string result = "QUOTE";
	type = SYMBOL;
	return result;
}

void Reader::nextToken() {
	char ic;
	tokenType_ = UNKNOWN;
    BOOST_LOG_TRIVIAL(trace) << "Get next token";
	while((input_.good()) && (tokenType_ == UNKNOWN))  {
		input_.get(ic);
		if(ic == ')') {
			tokenType_ = RPAREN;
			token_ = std::string(")");
			BOOST_LOG_TRIVIAL(trace) << "RPAREN";
			break;
		}
		if(ic == '(') {
			tokenType_ = LPAREN;
			token_ = std::string("(");
			BOOST_LOG_TRIVIAL(trace) << "LPAREN";
			break;
		}
		if (ic == '.') {
			tokenType_ = PERIOD;
			token_ = std::string(".");
			BOOST_LOG_TRIVIAL(trace) << "PERIOD";
			break;
		}
		if(ic == '\"') {
			token_ = readString();
			BOOST_LOG_TRIVIAL(trace) << "STRING";
			tokenType_ = STRING;
			break;
		}
		if(ic == '#') {
			BOOST_LOG_TRIVIAL(trace) << "CHAR";
			token_ = readChar();
			tokenType_ = CHAR;
		}
			
		if(ic == '\'') {
			BOOST_LOG_TRIVIAL(trace) << "QUOTE";
			token_ = readQuote(tokenType_);
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

bool Reader::isPeriodNext() {
	bool result = false;
	char ic;
	while (input_.good()) {
		input_.get(ic);
		if (!isspace(ic)) {
			if (ic == '.') {
				result = true;
			} else {
				input_.putback(ic);
			}
			break;
		}
	}
	return result;
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
	if (tokenType_ == PERIOD) {
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
	if (is_nil(car) && (tokenType_ == RPAREN))
		return nil;	
	if (isPeriodNext()) {
		LispObjRef cdr = read();
		LispObjRef result =  make_cons(car,cdr);
		if (tokenType_ != RPAREN) {
			std::cerr << "Badly formed s-expression" << std::endl;
			return nil;
		}
		return result;
	}
	LispObjRef cdr = read_list();
	return make_cons(car, cdr);
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

