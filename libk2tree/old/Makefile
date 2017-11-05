CXX = clang++
HEADERS = $(shell find include tests -name *.h)
INCLUDE = -Iinclude/

TESTS_SRC = $(shell find tests -name *.cc)
TESTS_OBJ = $(TESTS_SRC:%.cc=obj/%.o) 

K2TREE_SRC = $(shell find src/libk2tree -name *.cc)
K2TREE_OBJ = $(K2TREE_SRC:%.cc=obj/%.o)

DACS = dacs

FLAGS = -std=c++11 -O3 -Wall -Wextra -Wpedantic -DNDEBUG
FLAGS = -std=c++11 -O2 -g -Wall -Wextra -Wpedantic\
				-Wconversion -Wsign-conversion
LIBRARIES = -Llib -L$(DACS) -lcds2 -lboost_filesystem -lboost_system -lk2tree\
						-ldacs -lboost_program_options


.PHONY: clean style test all

lib: $(K2TREE_OBJ)
	ar rvs lib/libk2tree.a $(K2TREE_OBJ)

all: lib test build_k2tree time qry_gen

# DACS
dacs: $(DACS)/libdacs.a

$(DACS)/libdacs.a:
	@make -C $(DACS)
# END DACS
#
#
header: $(HEADERS)
	@$(CXX) $(INCLUDE) $(FLAGS) include/k2tree.h


# TEST
test: bin/test

bin/test: $(TESTS_OBJ)
	@echo " [LNK] Linking test"
	@$(CXX) -isystem $(GTEST)/include $(TESTS_OBJ) -lpthread  $(LIBRARIES)\
					-lgtest -o bin/test


obj/tests/%.o: tests/%.cc
	@echo " [C++] Compiling $<"
	@$(CXX) -isystem $(GTEST)/include $(INCLUDE) $(FLAGS) -c $< -o $@
# END TEST



# STYLE
style:
	@echo " [CHK] Cheking Code Style"
	@./cpplint.py --filter=-legal,-runtime/threadsafe_fn $(TESTS_SRC) $(K2TREE_SRC) $(HEADERS)
# END STYLE



# K2TREE

build_k2tree: bin/build_k2tree
time: bin/time
qry_gen: bin/qry_gen

bin/qry_gen:  obj/src/qry_gen.o
	@echo " [LNK] Linking qry_gen"
	@$(CXX) obj/src/qry_gen.o $(LIBRARIES) -o bin/qry_gen

bin/time:  obj/src/time.o
	@echo " [LNK] Linking time"
	@$(CXX) $(FLAGS) obj/src/time.o $(LIBRARIES) -o bin/time

bin/build_k2tree:  obj/src/build_k2tree.o
	@echo " [LNK] Linking build_k2tree"
	@$(CXX) obj/src/build_k2tree.o $(LIBRARIES) -o bin/build_k2tree

obj/src/build_k2tree.o: src/build_k2tree.cc
	@echo " [C++] Compiling $<"
	@$(CXX) $(INCLUDE) $(FLAGS) -c $< -o $@

obj/src/time.o: src/time.cc
	@echo " [C++] Compiling $<"
	@$(CXX) $(INCLUDE) $(FLAGS) -c $< -o $@

obj/src/qry_gen.o: src/queries_generator.cc
	@echo " [C++] Compiling $<"
	@$(CXX) $(INCLUDE) $(FLAGS) -c $< -o $@
obj/src/%.o: src/%.cc
	@echo " [C++] Compiling $<"
	@$(CXX) $(INCLUDE) $(FLAGS) -c $< -o $@
# END K2TREE


# CLEAN
clean : clean_k2tree clean_test

clean_test:
	@echo " [CLN] Cleaning test"
	@touch .dummy
	@rm $(shell find obj/tests -name *.o) .dummy
	@rm bin/test -f

clean_k2tree:
	@echo " [CLN] Cleaning k2tree"
	@touch .dummy
	@rm $(shell find obj/src -name *.o) .dummy
# END CLEAN
