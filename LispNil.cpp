
#include "LispObj.h"
#include "LispNil.h"

using namespace Lisp;

NIL::NIL()
{
}

NIL::NIL(const NIL& other)
{
}

Obj::eObjectType NIL::getObjectType() const
{
    return Obj::eNullObj;
}

NIL* NIL::create() const
{
    return new NIL();
}


NIL* NIL::clone() const
{
    return new NIL(*this);
}

void NIL::print(std::ostream& out) const
{
    out << " NIL ";    
}

bool NIL::operator==(const Obj* other)
{
    return (other->getObjectType() == Obj::eNullObj);
}
