
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <cassert>

#include "LispObj.h"
#include "LispNil.h"

using namespace Lisp;

LispEnv* LispEnv::root_environment = NULL;
LispEnv* LispEnv::current_environment = NULL;

int main(int argc, char** argv)
{
    
    LispEnv root;
}
