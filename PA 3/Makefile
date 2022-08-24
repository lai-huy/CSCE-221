all: bst avl

clean: 
	rm -f *.gcov *.gcda *.gcno a.out
	
compile_test: clean binary_search_tree.h avl_tree.h compile_test.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g compile_test.cpp

bst: clean binary_search_tree.h binary_search_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage binary_search_tree_tests.cpp && ./a.out && gcov -mr binary_search_tree_tests.cpp

avl: clean avl_tree.h avl_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage avl_tree_tests.cpp && ./a.out && gcov -mr avl_tree_tests.cpp

build_a_tree: clean binary_search_tree.h avl_tree.h build_a_tree.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g build_a_tree.cpp && ./a.out
