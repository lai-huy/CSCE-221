all: array_list linked_list stack queue

clean: 
	rm -f *.gcov *.gcda *.gcno a.out
	
compile_test: clean array_list.h doubly_linked_list.h stack.h queue.h compile_test.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -g compile_test.cpp

array_list: clean array_list.h array_list_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -g --coverage array_list_tests.cpp && ./a.out && gcov -mr array_list_tests.cpp

linked_list: clean doubly_linked_list.h doubly_linked_list_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -g --coverage doubly_linked_list_tests.cpp && ./a.out && gcov -mr doubly_linked_list_tests.cpp

stack: clean stack.h stack_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -g --coverage stack_tests.cpp && ./a.out && gcov -mr stack_tests.cpp
	
queue: clean queue.h queue_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -g --coverage queue_tests.cpp && ./a.out && gcov -mr queue_tests.cpp