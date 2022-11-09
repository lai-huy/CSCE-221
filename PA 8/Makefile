CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o main.out

objects = sorts

all:  $(objects)

memory_errors: sorts_memory_errors

compile_test: sorts_compile_test

clean: 
	rm -f *.gcov *.gcda *.gcno *.out
	
$(objects): %: clean %.h %_tests.cpp
	g++ $(CXXFLAGS) --coverage $@_tests.cpp
	./main.out
	gcov -mr $@_tests.cpp
	
sorts_memory_errors: %_memory_errors: clean %.h %_tests.cpp
	g++ $(CXXFLAGS) sorts_tests.cpp
	valgrind --leak-check=full ./main.out

sorts_compile_test: %_compile_test: %.h %.cpp
	g++ $(CXXFLAGS) sorts.cpp