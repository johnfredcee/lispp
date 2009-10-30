
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

namespace Lisp
{

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



// placeholder type
	struct NullType {
	private:
		const u32 dead_;
	public:
		NullType() : dead_(0xDEADBEEF)
		{

		}
	};

	
	template <typename T> class TUnboxedType
	{
	private:
		T data_;
	public:
		TUnboxedType() {

		}

		TUnboxedType(const TUnboxedType<T>& other) : data_(other.data_)
		{

		}

		T& operator=(const TUnboxedType<T>& other)
		{
			data_ = other.data_;
		}

		operator T()
		{
			return data_;
		}

		const bool isBoxed() const
		{
			return false;
		}
	};

	class CharType : public TUnboxedType<u8>
	{

	};

	class FixnumType : public TUnboxedType<u32>
	{
	};

	class FloatnumType : public TUnboxedType<f32>
	{
	};

	template <typename T> class TBoxedType
	{
	private:
		boost::shared_ptr<T> pointer_;
	public:
		TBoxedType() : pointer_(new T)
		{
		}

		TBoxedType(const TUnboxedType<T>& other) : pointer_(other.pointer_)
		{
		}

		T& operator=(const TBoxedType<T>& other)
		{
			pointer_ = other.pointer_;
		}

		T* operator->()
		{
			return pointer_.operator->();
		}

		T& operator*()
		{
			return pointer_.operator*();
		}

		const bool isBoxed() const
		{
			return true;
		}

	};

// Simple unboxable Lisp Value
	template <typename CharT,  typename FixnumT,  typename FloatnumT,  typename PrimT,  typename ObjRefT> class TLispValue
	{
	public:
		typedef CharT LispCharT;
		typedef FixnumT LispFixnumT;
		typedef FloatnumT LispFloatnumT;
		typedef PrimT LispPrimT;
		typedef ObjRefT LispObjRefT;

		boost::variant<  CharT,  FixnumT,  FloatnumT,  PrimT,  ObjRefT>	value_;

		CharT getChar() {
			return boost::get< CharT>(value_);
		}

		FixnumT getFixnum() {
			return boost::get< FixnumT>(value_);
		}

		FloatnumT getFloatNum() {
			return boost::get< FloatnumT>(value_);
		}

		PrimT getPrim() {
			return boost::get< PrimT>(value_);
		}
	};

// instantiate lisp value
	struct LispValue : public TLispValue<u8, u32, f32, NullType, boost::shared_ptr<void*> >
	{
	};

// Compound lisp object
	template <typename ListT, typename MapT, typename ArrayT> class TLispObj
		: public boost::variant<ListT, MapT, ArrayT>
	{
	public:
		const bool isCompound() const {
			return true;
		}
	};


	struct LispObject : public TLispObj<std::list<LispValue>, std::map<std::string, LispValue>, std::vector<LispValue> >
	{

	};

	class IsRefCompoundVisitor : public boost::static_visitor<>
	{
		bool isCompound_;

		template <typename T>
		void operator()(T& operand)
		{
			isCompound_ = operand->isCompound();
		}
	};


// reference to a lisp object: can either contain the value itself or a pointer to a compound value
	template <typename LispValueT, typename LispObjT> class LispObjRefT : 	public boost::variant< LispValueT, boost::shared_ptr<LispObjT> >
	{
	public:

		const bool isCompoundRef() const {
			IsRefCompoundVisitor visitor;
			boost::apply_visitor(this);
			return visitor.isCompound_;
		}
	};

	class LispObjRef : public LispObjRefT< LispValue, LispObject >
	{

	};



// This is our container primitive, the equivalent of a cons cell structured list
	template <typename D, template <typename> class C>
	class TLispObjContainer
	{
	public:

		typedef D ValueType;  
		typedef C<D> ValueContainerType;

		typename D::LispCharT getChar(std::size_t i)
		{
			return values[i].getChar();
		}

		typename D::LispFixnumT getFixnum(std::size_t i)
		{
			return values[i].getFixnum();
		}

		typename D::LispFloatnumT getFloatNum(std::size_t i)
		{
			return values[i].getFloatNum();
		}

		typename D::LispObjRefT getObjRef(std::size_t i)
		{
			return values[i].getObjRef();
		}

		ValueContainerType values;

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

	struct LispObjContainer {
		TLispObjContainer<LispValue, std::vector>  objects;
	};

} // end namespace lisp


#endif


