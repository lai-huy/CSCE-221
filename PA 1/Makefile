selection = selection.cpp selection_tests.cpp
collection = collection_tests.cpp

run_selection: clean build_selection
	./main.out

run_collection: clean build_collection
	./main.out

build_selection:
	g++ -std=c++17 -g -Wall -Wextra -Weffc++ -pedantic-errors -fsanitize=address,undefined -o main.out $(selection)

build_collection:
	g++ -std=c++17 -g -Wall -Wextra -Weffc++ -pedantic-errors -fsanitize=address,undefined -o main.out $(collection)

coverage_selection: clean $(selection)
	g++ -std=c++17 -g --coverage -o coverage.out $(selection)
	./coverage.out
	gcov -mr $(selection)

coverage_collection: clean $(collection)
	g++ -std=c++17 -g --coverage -o coverage.out $(collection)
	./coverage.out
	gcov -mr $(collection)

unsanitized_selection: clean $(selection)
	g++ -std=c++17 -g -Wall -Wextra -Weffc++ -pedantic-errors -o unsanitized.out $(selection)

unsanitized_collection: clean $(collection)
	g++ -std=c++17 -g -Wall -Wextra -Weffc++ -pedantic-errors -o unsanitized.out $(collection)

check_selection: clean unsanitized_selection
	valgrind --leak-check=full --show-leak-kinds=all -s ./unsanitized.out

check_collection: clean unsanitized_collection
	valgrind --leak-check=full --show-leak-kinds=all -s ./unsanitized.out

clean:
	rm -f *.out *.debug *.gcno *.gcda *.gcov *.s