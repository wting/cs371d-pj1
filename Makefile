### macro definitions
PROJ = Node
SVN_LOC = http://cs371d-pj1.googlecode.com/svn/trunk/

SYS = cs.utexas.edu
MAIN = main
EXT = cpp
APP = node
INPUT = input

TEST = Test$(PROJ)
IN_PROF = in_profile
SVN_FILE = Subversion.log

### compiler definitions
CC = g++
CFLAGS = -ansi -pedantic -Wall

ifeq ($(SYS),cs.utexas.edu)
	CC+=-I /public/linux/include/boost-1_38/
else
	CC+=-std=gnu++0x
endif

#ifeq (`hostname | cut -d. -f2-`,cs.utexas.edu) #conditional not working
	#CC = /lusr/opt/gcc-4.3.0/bin/g++
#else
	#CC = g++
#endif



### make options
main: $(MAIN).$(EXT)
	clear
	echo $(SYS)
	$(CC) $(CFLAGS)	-O2 -o $(APP) $(MAIN).$(EXT)
	#valgrind $(APP) <$(INPUT) 
	./$(APP)

profile: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS) -pg -O2 -DONLINE_JUDGE -DPROFILE -o $(APP) $(MAIN).$(EXT)
	./$(APP) <$(IN_PROF) >/dev/null
	gprof ./$(APP) >gprof.out
	head -n20 gprof.out

debug: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS)	-O2 -DDEBUG_OUTPUT -o $(APP) $(MAIN).$(EXT)
	./$(APP) <$(INPUT)
	#valgrind $(APP) <$(INPUT) >$(PROJ).out 2>&1
	#less $(PROJ).out
	#rm -f $(PROJ).out

gdb: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS) -ggdb -DDEBUG_OUTPUT -o $(APP) $(MAIN).$(EXT)
	gdb $(APP)

test: $(TEST).h 
	clear
	###Compiling...
	$(CC) $(CFLAGS) -lcppunit -ldl -DTEST -o $(APP) $(MAIN).$(EXT)
	###Valgrind...
	valgrind $(APP) >$(TEST).out 2>&1 && cat $(TEST).out || ./$(APP)

debug-test: $(MAIN).$(EXT)
	clear
	###Compiling...
	$(CC) $(CFLAGS) -lcppunit -ldl -DDEBUG_OUTPUT -DTEST -o $(APP) $(MAIN).$(EXT)
	###Valgrind...
	./$(APP) >$(PROJ).out 2>&1 && less $(PROJ).out || ./$(APP)

clean:
	rm -f $(APP)
	rm -f *.out

docs: Doxyfile
	doxygen Doxyfile

doxyfile:
	doxygen -g

log:
	svn log $(SVN_LOC) >$(SVN_FILE)
	head -n20 $(SVN_FILE)
