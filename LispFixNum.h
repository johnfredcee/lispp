
#ifndef LISP_FIXNUM_H_INCLUDED
#define LISP_FIXNUM_H_INCLUDED

namespace Lisp
{
    
    class LispFixNum : public LispObj
    {
            
        public:
            LispObj::eLispObjectType getObjectType() const;
            LispFixNum* create() const;
            LispFixNum* clone() const;
            void print(std::ostream& out) const;
            bool operator==(const LispObj* other);
            operator const FixNumValue() const { return m_fixnum; };

        protected:
            LispFixNum(FixNumValue value = 0);
            LispFixNum(const LispFixNum& other);
        private:
            FixNumValue m_fixnum;
    };
}

#endif
