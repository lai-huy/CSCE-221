CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o main.out

objects = heap priority_queue

all:  $(objects)

memory_errors: heap_memory_errors priority_queue_memory_errors

compile_test: heap_compile_test priority_queue_compile_test

clean: 
	rm -f *.gcov *.gcda *.gcno *.out
	
$(objects): %: clean %.h %_tests.cpp
	g++ $(CXXFLAGS) --coverage $@_tests.cpp
	./main.out
	gcov -mr $@_tests.cpp
	
heap_memory_errors: %_memory_errors: clean %.h %_tests.cpp
	g++ $(CXXFLAGS) heap_tests.cpp
	valgrind --leak-check=full ./main.out
	
priority_queue_memory_errors: %_memory_errors: clean %.h %_tests.cpp
	g++ $(CXXFLAGS) priority_queue_tests.cpp
	valgrind --leak-check=full ./main.out

heap_compile_test priority_queue_compile_test: %_compile_test: %.h %_compile_test.cpp
	g++ $(CXXFLAGS) $@.cpp