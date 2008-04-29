
#include "LispObj.h"
#include "LispNil.h"

using namespace Lisp;

LispNIL::LispNIL()
{
}

LispNIL::LispNIL(const LispNIL& other)
{
}

LispObj::eLispObjectType LispNIL::getObjectType() const
{
    return LispObj::eNullObj;
}

LispNIL* LispNIL::create() const
{
    return new LispNIL();
}


LispNIL* LispNIL::clone() const
{
    return new LispNIL(*this);
}

void LispNIL::print(std::ostream& out) const
{
    out << " NIL ";    
}

bool LispNIL::identify(std::string in) const
{
    return in == "NIL";
}

bool LispNIL::operator==(const LispObj* other)
{
    return (other->getObjectType() == LispObj::eNullObj);
}
