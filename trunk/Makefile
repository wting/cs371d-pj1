### macro definitions
PROJ = Node
SVN_LOC = http://cs371d-pj1.googlecode.com/svn/trunk/

MAIN = main
EXT = cpp
APP = node
INPUT = input
SVN_FILE = Subversion.log

### compiler definitions
CC = g++
CFLAGS = -o $(APP) -ansi -pedantic -Wall -pthread -O2

ifeq ($(shell hostname | cut -d. -f2-),cs.utexas.edu)
	INC = -I /public/linux/include/boost-1_38/ #for cs machines
	LIB = /public/linux/lib/libboost_system-gcc42-mt-1_38.a
else
	INC = -I ~/boost_1_38_0/
endif
CFLAGS += $(INC)

### make options
main: $(MAIN).$(EXT)
	clear
	### COMPILING
	$(CC) $(CFLAGS)	$(MAIN).$(EXT) $(LIB)
	@#valgrind $(APP) <$(INPUT) 

	@echo "\n"
	### EXECUTING
	@./$(APP)

debug: $(MAIN).$(EXT)
	clear
	### COMPILING
	$(CC) $(CFLAGS)	-DDEBUG $(MAIN).$(EXT) $(LIB)

	@echo "\n"
	### EXECUTING
	@./$(APP) <$(INPUT)
	@#valgrind $(APP) <$(INPUT) >$(PROJ).out 2>&1
	@#less $(PROJ).out
	@#rm -f $(PROJ).out

gdb: $(MAIN).$(EXT)
	clear
	$(CC) $(CFLAGS) -ggdb -DDEBUG $(MAIN).$(EXT)
	gdb $(APP)

clean:
	rm -f $(APP)
	rm -f *.out
	rm -f *.log

docs: Doxyfile
	doxygen Doxyfile

doxyfile:
	doxygen -g

log:
	svn log $(SVN_LOC) >$(SVN_FILE)
	head -n20 $(SVN_FILE)
