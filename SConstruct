import os

vars = Variables('custom.py')
vars.Add(PathVariable('BOOST', 'Path to boost', '/usr/include/boost'))
if os.name == "posix":
	env = Environment(variables=vars)
else:
	env = Environment(variables=vars, tools = [ 'mingw' ])
env.Append(CXXFLAGS=[ "-g", "-O0", "-Wall" ])
env.Append(CPPPATH = [ env['BOOST'] ])
env.Program("lispp", [ "Main.cpp", "LispObj.cpp", "LispReader.cpp", "LispFixNum.cpp", "LispFloatNum.cpp", "LispChar.cpp", "LispNil.cpp" , "LispCons.cpp", "LispString.cpp", "LispSymbol.cpp", "LispPrinter.cpp", "LispEnv.cpp", "LispEval.cpp", "LispPrimitive.cpp", "LispQuote.cpp" ])

