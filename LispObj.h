
#ifndef H_LISP_OBJ
#define H_LISP_OBJ

#include <cassert>
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>

namespace Lisp {

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long s64;
typedef signed long long s128;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned long long u128;

typedef float f32;
typedef double f64;

// forward declaration
class LispObj;

typedef boost::shared_ptr<LispObj> LispObjRef;

typedef s32 CFixnum;
typedef u8  CChar;
typedef std::string CString;
typedef f32 CFloatnum; 

// placeholder type
class NullType {
private:
	const u32 dead_;
public:
	NullType() : dead_(0xDEADBEEF) {
	}
};

/* This is a template for an unboxed type that can be represented by a simple scalar */
template <typename T> class TLispType {
private:
	T data_;
public:
	TLispType() {
	}
		
	explicit TLispType(const T& other) : data_(other) {
	}

	T& operator=(const T& other) {
		data_ = other;
	}

	TLispType(const TLispType<T>& other) : data_(other.data_) {
	}

	T& operator=(const TLispType<T>& other) {			
		data_ = other.data_;
		return *this;
	}

	// unboxed types can be freely converted to C++ type
	operator T() {
		return data_;
	}

};

class LispPrimitive 
{
	LispObjRef operator()(LispObjRef args);
};

typedef std::pair< std::string, LispObjRef > LispSymbol;

/* byte */
typedef TLispType<CChar> CharType;

/* fixnum */
typedef TLispType<CFixnum> FixnumType;

/* float */
typedef TLispType<CFloatnum> FloatnumType;

/* string */
typedef TLispType< CString	> StringType;

/* symbol */
typedef TLispType< LispSymbol >	 SymbolType;

/* cons cell */
typedef std::pair< LispObjRef, LispObjRef > CCons;
typedef TLispType< CCons >  ConsType;

/** primitive */
typedef	 TLispType< LispPrimitive > PrimType;

enum LispObjectType {
	NIL = 0,
	CHAR,
	FIXNUM,
	FLOATNUM,
	SYMBOL,
	STRING,
	CONS,
	PRIM
};

	
typedef	 boost::variant< NullType, CharType, FixnumType, FloatnumType, SymbolType, StringType, ConsType, PrimType > LispObjBase;
	
class LispObj : public LispObjBase {
public:
	LispObj() : LispObjBase() {
			
	}
	LispObj(const FixnumType& fnum) : LispObjBase(fnum) {
			
	}
	LispObj(const FloatnumType& fnum) : LispObjBase(fnum) {
			
	}
	LispObj(const CharType& ch) : LispObjBase(ch) {
			
	}
	LispObj(const ConsType& cons) : LispObjBase(cons) {			
	}

	LispObj(const StringType& string) : LispObjBase(string) {
			
	}

	LispObj(const SymbolType& symbol) : LispObjBase(symbol) {
			
	}
};

} // end namespace lisp


#endif


