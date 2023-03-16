CC = g++
CFLAGS = -Wall -Werror -Wextra
TEST_OUT = tests.out

all: clean s21_matrix_oop.a gcov_report

clean:
	@rm -rf report *.o *.a *.gcda *.gcno *.info *.out *.txt $(TEST_OUT)

s21_matrix_oop.a:
	@$(CC) $(CFLAGS) -c s21_matrix_oop.cpp
	@ar rc s21_matrix_oop.a s21_matrix_oop.o
	@ranlib s21_matrix_oop.a
	@rm s21_matrix_oop.o

test:
	@$(CC) $(CFLAGS) tests/tests.cpp s21_matrix_oop.cpp -lgtest -pthread -o $(TEST_OUT)
	@./$(TEST_OUT)

gcov_report:
	@$(CC) $(CFLAGS) tests/tests.cpp s21_matrix_oop.cpp -lgtest --coverage -o report.out
	@./report.out
	@lcov -t "report" -o report.info --no-external -c -d .
	@genhtml -o ./report report.info
	@rm -rf *.gcda *.gcno *.info *.out
	@open ./report/src/index.html

rebuild: clean all

check_leak: clean test
	@valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=out_valgrind.txt ./$(TEST_OUT)
	@rm $(TEST_OUT)

check_style:
	@clang-format -style=Google -n *.cpp tests/tests.cpp *.h 

correct_style:
	@clang-format -style=Google -i *.cpp tests/tests.cpp *.h 

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ *.cpp tests/tests.cpp *.h 

cpplint:
	@python3 cpplint.py --extensions=cpp *.cpp tests/tests.cpp *.h 

all_check: check_style cppcheck cpplint

git:
	@git add .
	@git commit -m "$(c)"
	@git push
# make git c=commit