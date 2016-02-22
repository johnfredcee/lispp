
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

class LispEnv;

typedef boost::shared_ptr<LispEnv> LispEnvRef;

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
  NullType() :dead_(0xDEADBEEF) {
  }
};

/* This is a template for an unboxed type that can be represented by a simple scalar */
template <typename T> class TLispType {
private:
	T data_;
public:
	typedef T CType;
	
	TLispType<T>() {
	}
	  
	explicit TLispType<T>(const T& other) : data_(other) {
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

/**
 * LispPrimitive is a pointer to a function that returns a reference to 
 * a lisp obj and takes in a lisp obj. 
 */
typedef LispObjRef (*CPrim)(LispObjRef args, LispEnvRef env);

/* symbol : a name that references an object */ 
struct LispSymbol
{
	std::string name;
	LispObjRef value;
	
	LispSymbol(const std::string& n, const LispObjRef& v) : name(n), value(v)
	{
	};

  LispSymbol(const LispSymbol& sym) : name(sym.name), value(sym.value)
 {
 }
};


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
typedef	 TLispType< CPrim > PrimType;

/* lambda */
typedef struct Lambda { LispObjRef args; LispObjRef body; Lambda() : args(LispObjRef()), body(LispObjRef()) {}; Lambda(LispObjRef a, LispObjRef b) : args(a), body(b) {}; } CLambda;

typedef TLispType< CLambda > LambdaType;

enum LispObjectType {
	NIL = 0,
	CHAR,
	FIXNUM,
	FLOATNUM,
	SYMBOL,
	STRING,
	CONS,
	PRIM,
	LAMBDA
};

	
typedef	 boost::variant< NullType, CharType, FixnumType, FloatnumType, SymbolType, StringType, ConsType, PrimType, LambdaType > LispObjBase;
	
class LispObj : public LispObjBase {
public:
	LispObj() : LispObjBase() {
	}
	
	template <typename T>
	LispObj(const T& obj) : LispObjBase(TLispType<T>(obj)) {
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

	LispObj(const PrimType& primitive) : LispObjBase(primitive) {	
	}

	LispObj(const LambdaType& lambda) : LispObjBase(lambda) {
	}
};

template <typename T>
inline LispObjRef make_literal(const T& literal)
{
	return boost::shared_ptr<LispObj>(new LispObj(literal));
}

typedef const char *cstrptr;

template <>
inline LispObjRef make_literal(const cstrptr& literal)
{
	std::string str(literal);
	return boost::shared_ptr<LispObj>(new LispObj(str));	
}

template <class LT>
inline typename LT::CType get_ctype(LispObjRef obj)
{
	return ((typename LT::CType)(boost::get<LT>(*obj))); 
}


} // end namespace lisp



#endif


