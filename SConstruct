
import os
import tempfile
import shlex
import subprocess
import sys

vars = Variables('custom.py')
vars.Add(BoolVariable('SYNTAX', 'Set to 1 for a syntax check',0))
vars.Add(PathVariable('BOOST', 'Path to boost', '/usr/include/boost'))
vars.Add(EnumVariable('DUMPENV', 'Set to var to dump environment', 'NONE',
		      [ 'NONE', 'CPPPATH', 'CPPFLAGS']))
#vars.Add(PathVariable('BOOST', 'Path to boost', r'w:\tools_libraries\boost'))

if os.name == "posix":
	env = Environment(variables=vars)
else:
	env = Environment(ENV=os.environ, variables=vars,  tools = [ 'mingw' ])
env.Append(CXXFLAGS=[ "-g", "-O0", "-Wall" ])
env.Append(CPPPATH = [ env['BOOST'] ])
if (env["SYNTAX"] == 1):
	env.Append(CCFLAGS=["-fsyntax-only"])
env.Append(LIBS = ["boost_log_setup", "boost_log", "boost_thread", "boost_date_time", "boost_atomic", "boost_filesystem", "boost_system" ])

def run_etags(env, target, source):
	listfile = tempfile.NamedTemporaryFile(mode="w+", dir=os.getcwd(), delete=False)
	listname = listfile.name
	for sfile in source:
		print >>listfile, str(sfile)
	listfile.close()
	etagargs = shlex.split("ctags -e --options=.etags --verbose --c++-kinds=cfnstunedm --extra=+q  -o %s -L %s" % (target[0], listname))
	print etagargs
	try:
		retcode = subprocess.call(etagargs)
		if retcode < 0:
			print >>sys.stderr, "Child was terminated by signal", -retcode
                else:
			print >>sys.stderr, "Child returned", retcode
	except OSError, e:
		print >>sys.stderr, "Execution failed:", e
	os.remove(listname)

sources = [ "Main.cpp", "LispObj.cpp", "LispReader.cpp", "LispFixNum.cpp", "LispFloatNum.cpp", "LispChar.cpp", "LispNil.cpp" , "LispCons.cpp", "LispString.cpp", "LispSymbol.cpp", "LispPrinter.cpp", "LispEnv.cpp", "LispEval.cpp", "LispPrimitive.cpp", "LispQuote.cpp" ]
objects = [os.path.splitext(s)[0] + ".o" for s in sources]

# needs to change - needs to get .cpp / .c file on command line and build
if (env["SYNTAX"]==1):
	print "Syntax checking %s " % str(COMMAND_LINE_TARGETS)
	env.StaticObject(COMMAND_LINE_TARGETS[0], os.path.splitext(COMMAND_LINE_TARGETS[0])[0] + ".cpp")
else:
	for s,o in zip(sources,objects):
		env.StaticObject(o,s)
	env.Program("lispp", sources)
#	env.Command("TAGS", env.Glob(r"*.cpp")  + env.Glob(r"*.h"), [ run_etags ])


