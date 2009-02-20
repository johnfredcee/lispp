
#ifndef H_LISP_OBJ
#define H_LISP_OBJ

#include <cassert>
#include <ostream>
#include <vector>
#include <string>
#include <algorithm>

namespace Lisp
{
	


enum eObjectType
{
	eBaseObj  = 0,
	eNullObj,
	eStringObj,
	eConsObj,
	eFixnumObj,
	eFloatnumObj,
	eSymbolObj,
	ePackageObj,
	eFunctionObj
};


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

typedef u8 CharType;
typedef u32 FixnumType;
typedef f32 FloatnumType;


struct LispObj;

// smart pointer for pointing at lisp objects
template <typename T> class ObjPtr
{
public:	
	typedef T* ActualPtrType;
	explicit ObjPtr( T* o ) : p_(o) {};
//	~ObjPtr( ) { delete p_; }
	T* operator->() { return get(); };
	T& operator*() { return *get(); };

	template <typename D>
	operator ObjPtr<D>()
	{
		return ObjPtr<D>(p_);
	}
	
private:
	explicit ObjPtr( void* o ) : p_(static_cast<T*>(o)) {};
	
	T* get() const
	{
		return p_;
	}
	
	void set(const void *p)
	{
		p_ = reinterpret_cast<T*>(p);
	}

	T* p_;

	template <typename ActualT, typename CharT, typename FixnumT, typename FloatnumT, typename PrimType, typename PtrType>
	friend class TLispValue;
};

// this is what we use to point at a lisp object
typedef ObjPtr<LispObj> PointerType;


// straight primitive call with no environment / args
template <typename ArgPointer, template <typename> class ArgContainer>
class PrimitiveT
{
public:
    // err..what does a smart pointer to a pointer look like?
	typedef PointerType (*PrimitivePtr)(ArgContainer<ArgPointer>& args);
	
	explicit PrimitiveT(PrimitivePtr f) : fn_(f) {}
	PointerType operator()(ArgContainer<ArgPointer>& p)
 	{
 		return fn_(p);
 	}
 private:
 	PrimitivePtr fn_;
};

typedef PrimitiveT< ObjPtr<LispObj>, std::vector > PrimitiveType;



// Primitive unboxed values (this must be POD)
template <typename ActualT, typename CharT, typename FixnumT, typename FloatnumT, typename PrimT, typename PtrT> class TLispValue
{
public:	
	ActualT value;

	TLispValue()
	{
	}
	
	// need to be ablue to convert between ActualType and these types
	operator PtrT() const
	{
		// convert it to a void * and construct a PtrT() around it
		return PtrT(reinterpret_cast<void*>(value));
	}

	
	// we can't overload by return type, so we use value conversion instead
	operator FixnumT() const
	{
		return value;
	};
	
	operator FloatnumT() const
	{
		return *(static_cast<FloatnumT*>(&value));
	}

	operator CharT() const
	{
		return *(static_cast<CharT*>(&value));
	};

	operator PrimT() const
	{
		return *(static_cast<PrimT*>(&value));
	}

	TLispValue(const PtrT& ptr)
	{
		value = reinterpret_cast<ActualT>(reinterpret_cast<void*>(ptr.get()));
	}
	
	TLispValue& operator=(const PtrT& ptr)
	{
		value = reinterpret_cast<ActualT>(reinterpret_cast<void*>(ptr.get()));
		return *this;
	}

	TLispValue(const FixnumT& fn)
	{
		value = fn;
	}
	
	TLispValue& operator=(const FixnumT& fn)
	{
		value = fn;
		return *this;
	}

	TLispValue(const FloatnumT& fn)
	{
		(*static_cast<FloatnumT*>(&value))  = fn;		
	}
	
	TLispValue& set(const FloatnumT& fn)
	{
		(*static_cast<FloatnumT*>(&value))  = fn;
		return *this;
	}

	TLispValue(const CharT& ch)
	{
		(*static_cast<FloatnumT*>(&value))  = ch;		
	}
	
	TLispValue& operator=(const CharT& ch)		
	{
		(*static_cast<CharT*>(&value))  = ch;
		return *this;
	}

	TLispValue(const PrimT& prim)
	{
		(*static_cast<FloatnumT*>(&value))  = prim;		
	}	
	
	TLispValue& operator=(const PrimT& prim)
	{
		(*static_cast<PrimT*>(&value))  = prim;
		return *this;
	}
	
};


// tag types (this doesn't have to be POD, but its advisable)
template <typename T> class Tag
{
private:	
	T tagValue;

public:	
	void setType(eObjectType tag)
	{
		tagValue = static_cast<eObjectType>(tagValue);
	}
	
	eObjectType getType()
	{
		static_cast<eObjectType>(tagValue);
	}
};

typedef Tag<u8> LispTag;
typedef TLispValue<u128, CharType, FixnumType, FloatnumType, PrimitiveType, PointerType> LispValue;


// container of object data with a tag
template <typename T, typename D, template <typename> class C>
class TaggedObjData
{
public:	

	typedef T TagType;
	typedef D ValueType;
	typedef C<D> ValueContainerType;

	T tag;
	ValueContainerType values;
	
	// T needs to implement sthing which will transform a tag to a
	// object type
	eObjectType getType()
	{
		return tag.getType(tag);
	}

	void setType(eObjectType type)
	{
		return tag.setType(type);
	}
	
	// container must have capacity
	void resize(std::size_t s)
	{
		values.reserve(s);
		values.resize(s);
	}

	// must be able to tell what that capacity is
	std::size_t size() const
	{
		return values.size();
	}

};

// TO DO -- template template parameters?

struct LispObj {
	TaggedObjData<Tag<unsigned char>, LispValue, std::vector>  object;
};






} // end namespace lisp
	

#endif


