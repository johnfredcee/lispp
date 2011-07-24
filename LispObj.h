
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

    // placeholder type
	class NullType {
	private:
		const u32 dead_;
	public:
		NullType() : dead_(0xDEADBEEF) {
		}
	};

	/* This is a template for an unboxed type that can be represented by a simple scalar */
	template <typename T> class TUnboxedType {
	private:
		T data_;
	public:
		TUnboxedType() {
		}
		
		explicit TUnboxedType(const T& other) : data_(other) {
		}

		T& operator=(const T& other) {
			data_ = other;
		}

		TUnboxedType(const TUnboxedType<T>& other) : data_(other.data_) {
		}

		T& operator=(const TUnboxedType<T>& other) {			
			data_ = other.data_;
			return *this;
		}

		operator T() {
			return data_;
		}

		const bool isBoxed() const {
			return false;
		}
	};

	template <typename T> class TBoxedType {
	private:

		T data_;

	public:
		TBoxedType() {
   		}

		TBoxedType(const T& other) : data_(other) {				
		}

		TBoxedType(const TBoxedType<T>& other) : data_(other.data_) {
		}

		T& operator=(const TBoxedType<T>& other) {
			if (this != &other)
				data_ = other.data_;
			return *this;
		}

		const bool isBoxed() const {
			return true;
		}

	};

	class LispPrimitive 
	{
		LispObjRef operator()(LispObjRef args);
	};
		
	/* byte */
	typedef TUnboxedType<u8> CharType;

	/* fixnum */
	typedef TUnboxedType<u32> FixnumType;

	/* float */
	typedef TUnboxedType<f32> FloatnumType;

	/* string */
	typedef TBoxedType< std::string  > StringType;

	/* symbol */
	typedef TBoxedType< std::pair< std::string, LispObjRef  > >  SymbolType;

	/* cons cell */
	typedef TBoxedType< std::pair< LispObjRef, LispObjRef > >  ConsType;

	/** primitive */
	typedef  TBoxedType< LispPrimitive > PrimType;

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

	
	typedef  boost::variant< NullType, CharType, FixnumType, FloatnumType, SymbolType, StringType, ConsType, PrimType > LispObjBase;
	
	class LispObj : public LispObjBase {
	public:
		LispObj(const FixnumType& fnum) : LispObjBase(fnum) {
			
		}
		LispObj(const FloatnumType& fnum) : LispObjBase(fnum) {
			
		}
		LispObj(const CharType& fnum) : LispObjBase(fnum) {
			
		}
	};

} // end namespace lisp


#endif


