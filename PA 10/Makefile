CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o main.out

objects = graph

all:  $(objects)

memory_errors: graph_memory_errors

compile_test: graph_compile_test

clean: 
	rm -f *.gcov *.gcda *.gcno *.out
	
$(objects): %: clean %.h %_tests.cpp
	g++ $(CXXFLAGS) --coverage $@_tests.cpp
	./main.out
	gcov --use-colors --demangled-names --object-file *.gcda $@_tests.cpp
	
graph_memory_errors: %_memory_errors: clean %.h %_tests.cpp
	g++ $(CXXFLAGS) graph_tests.cpp
	valgrind --leak-check=full ./main.out

graph_compile_test: %_compile_test: %.h %_compile_test.cpp
	g++ $(CXXFLAGS) $@.cpp
