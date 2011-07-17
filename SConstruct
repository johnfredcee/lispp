
vars = Variables('custom.py')
vars.Add(PathVariable('BOOST', 'Path to boost', '/usr/include/boost'))
env = Environment(variables=vars)
#env.Append(CXXFLAGS=[ "-g", "-Od" ])
env.Append(CPPPATH = [ env['BOOST'] ])
env.Program("lispp", [ "Main.cpp", "LispObj.cpp", "LispReader.cpp" ]) # , "LispNil.cpp", "LispCons.cpp", "LispSymbol.cpp" ])

