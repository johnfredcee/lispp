
#include <cassert>

#include <list>
#include <vector>
#include <iostream>
#include <string>

#include "LispObj.h"
#include "LispFixNum.h"

using namespace Lisp;

LispObj::eLispObjectType LispFixNum::getObjectType() const
{
    return LispObj::eFixNumObj;
}

LispFixNum* LispFixNum::create() const
{
    return new LispFixNum(0);
}

LispFixNum* LispFixNum::clone() const
{
    return new LispFixNum(*this);
}

void LispFixNum::print(std::ostream& out) const
{
    out << m_fixnum;
}

bool LispFixNum::operator==(const LispObj* other)
{
    return m_fixnum == (const FixNumValue)(*other);
}


LispFixNum::LispFixNum(FixNumValue value) : m_fixnum(value)
{
}

LispFixNum::LispFixNum(const LispFixNum& other)
{
    m_fixnum = other.m_fixnum;
}


