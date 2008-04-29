#if !defined(H_LISPNIL)
#define H_LISPNIL

namespace Lisp
{
    class LispNIL : public LispObj
    {
        public:
            LispObj::eLispObjectType getObjectType() const;
            LispNIL* create() const;
            LispNIL* clone() const;
            void print(std::ostream& out) const;
            bool identify(std::string in) const;
            bool operator==(const LispObj* other);
        protected:
            LispNIL();
            LispNIL(const LispNIL& other);
    };
}


#endif
