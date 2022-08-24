all: set map

clean:
	rm -f *.gcov *.gcda *.gcno a.out

set: clean my_set.h set_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage set_tests.cpp && ./a.out && gcov -mr set_tests.cpp

map: clean my_map.h map_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage map_tests.cpp && ./a.out && gcov -mr map_tests.cpp

set_memory_errors: clean my_set.h set_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g set_tests.cpp && valgrind --leak-check=full ./a.out

map_memory_errors: clean my_map.h map_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g map_tests.cpp && valgrind --leak-check=full ./a.out

compile_test: compile_test_set compile_test_map


compile_test_set: clean my_set.h compile_test_set.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g compile_test_set.cpp

compile_test_map: clean my_map.h compile_test_map.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g compile_test_map.cpp
