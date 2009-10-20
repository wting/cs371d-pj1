# macro definitions
PROJ = Node
SVN_LOC = http://cs371d-pj1.googlecode.com/svn/trunk/

MAIN = main
EXT = cpp
TEST = Test$(PROJ)
IN_PROF = in_profile
SVN_FILE = Subversion.log

# compiler definitions
CC = g++
CFLAGS = -ansi -pedantic -Wall

# make options
main: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS)	-O2 -o $(MAIN).app $(MAIN).$(EXT)
	valgrind $(MAIN).app >$(PROJ).out 2>&1
	less $(PROJ).out

profile: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS) -pg -O2 -DONLINE_JUDGE -DPROFILE -o $(MAIN).app $(MAIN).$(EXT)
	./$(MAIN).app <$(IN_PROF) >/dev/null
	gprof ./$(MAIN).app >gprof.out
	head -n20 gprof.out

debug: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS)	-O2 -DDEBUG_OUTPUT -o $(MAIN).app $(MAIN).$(EXT)
	./$(MAIN).app >$(PROJ).out 2>&1
	less $(PROJ).out

gdb: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS) -ggdb -DDEBUG_OUTPUT -o $(MAIN).app $(MAIN).$(EXT)
	gdb main.app

test: $(TEST).h 
	clear
	###Compiling...
	$(CC) $(CFLAGS) -lcppunit -ldl -DTEST -o $(MAIN).app $(MAIN).$(EXT)
	###Valgrind...
	valgrind main.app >$(TEST).out 2>&1 && cat $(TEST).out || ./main.app

debug-test: $(MAIN).$(EXT)
	clear
	###Compiling...
	$(CC) $(CFLAGS) -lcppunit -ldl -DDEBUG_OUTPUT -DTEST -o $(MAIN).app $(MAIN).$(EXT)
	###Valgrind...
	./$(MAIN).app >$(PROJ).out 2>&1 && less $(PROJ).out || ./main.app

docs: Doxyfile
	doxygen Doxyfile

doxyfile:
	doxygen -g

log:
	svn log $(SVN_LOC) >$(SVN_FILE)
	head -n20 $(SVN_FILE)
