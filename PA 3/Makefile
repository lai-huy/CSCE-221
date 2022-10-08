all: bst avl

clean: 
	rm -f *.gcov *.gcda *.gcno *.out

compile_test: clean binary_search_tree.h avl_tree.h compile_test.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o main.out compile_test.cpp

bst: clean binary_search_tree.h binary_search_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage -o main.out binary_search_tree_tests.cpp
	./main.out
	gcov -mr binary_search_tree_tests.cpp

bst_check: clean
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o unsainitized.out binary_search_tree_tests.cpp
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.out -s ./unsainitized.out

bst_time: clean
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o time.out bst_time.cpp
	./time.out

avl: clean avl_tree.h avl_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage -o main.out avl_tree_tests.cpp
	./main.out
	gcov -mr avl_tree_tests.cpp

avl_check: clean
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o unsainitized.out avl_tree_tests.cpp
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.out -s ./unsainitized.out

avl_time: clean
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o time.out avl_time.cpp
	./time.out

build_a_tree: clean binary_search_tree.h avl_tree.h build_a_tree.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o main.out build_a_tree.cpp
	./main.out
