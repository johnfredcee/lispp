
#ifndef H_LISP_OBJ
#define H_LISP_OBJ

#include <cassert>
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <boost/variant.hpp>
#include <boost/tr1/memory.hpp>

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

	class LispObjRef : public boost::shared_ptr<LispObj> {
		
	};

    // placeholder type
	struct NullType {
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

		TUnboxedType(const TUnboxedType<T>& other) : data_(other.data_) {
		}

		T& operator=(const TUnboxedType<T>& other) {
			data_ = other.data_;
		}

		operator T() {
			return data_;
		}

		const bool isBoxed() const {
			return false;
		}
	};

	/* byte */
	class CharType : public TUnboxedType<u8> {
	};

	/* fixnum */
	class FixnumType : public TUnboxedType<u32> {
	};

	/* float */
	class FloatnumType : public TUnboxedType<f32> {
	};


	/* string */
	class StringType : public std::string {		
	};

	/* cons cell */
	class ConsType : public std::pair< LispObjRef, LispObjRef > {		
	};

	/* template around a polymorphic simple unboxable Lisp Value */
	class LispObj : public boost::variant< NullType, CharType, FixnumType, FloatnumType, StringType, ConsType > 
	{
		
	};

} // end namespace lisp


#endif


