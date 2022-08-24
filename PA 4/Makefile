all: rbt

clean: 
	rm -f *.gcov *.gcda *.gcno a.out

rbt: clean red_black_tree.h red_black_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage red_black_tree_tests.cpp && ./a.out && gcov -mr red_black_tree_tests.cpp
	
memory_errors: clean red_black_tree.h red_black_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g red_black_tree_tests.cpp && valgrind --leak-check=full ./a.out

compile_test: clean red_black_tree.h compile_test_rbt.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g compile_test.cpp