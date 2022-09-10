all: rbt

clean: 
	rm -f *.gcov *.gcda *.gcno *.out

rbt: clean red_black_tree.h red_black_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage -o main.out red_black_tree_tests.cpp
	./main.out
	gcov -mr red_black_tree_tests.cpp
	
memory_errors: clean red_black_tree.h red_black_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o valgrind.out red_black_tree_tests.cpp
	valgrind --leak-check=full --show-leak-kinds=all -s ./valgrind.out

compile_test: clean red_black_tree.h compile_test_rbt.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o main.out compile_test.cpp