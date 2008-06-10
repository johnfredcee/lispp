#if !defined(H_LISPNIL)
#define H_LISPNIL

namespace Lisp
{
    class NIL : public Obj
    {
	public:

		Obj::eObjectType getObjectType() const;
		static NIL *make();
		NIL* create() const;
		NIL* clone() const;
		void print(std::ostream& out) const;
		bool operator==(const Obj* other);
	protected:
		NIL();
		NIL(const NIL& other);
    };
}


#endif
