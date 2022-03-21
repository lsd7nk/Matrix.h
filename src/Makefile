CC=gcc -std=c11
CFLAGS=-Wall -Wextra -Werror
LFLAGS = -lcheck -lm

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LFLAGS += -pthread -lcheck_pic -pthread -lrt -lsubunit
endif

FILE1=s21_matrix
FILE2=s21_matrix_tests

all:	s21_matrix.a test

test:	s21_matrix.a
	$(CC) $(CFLAGS) $(FILE2).c $(FILE1).a $(LFLAGS) -o test
	./test

s21_matrix.a: $(FILE1).o
	ar rcs $(FILE1).a $(FILE1).o
	ranlib $(FILE1).a
	cp $(FILE1).a lib$(FILE1).a

s21_matrix.o : $(FILE1).c $(FILE1).h
	$(CC) -c $(FILE1).c -o $(FILE1).o

gcov_report:
	$(CC) --coverage $(LDFLAGS) s21_matrix_tests.c $(FILE1).c -o s21_matrix_tests -lcheck
	./s21_matrix_tests
	lcov -t "tes21_matrix_tests" -o s21_matrix_tests.info -c -d ./
	genhtml -o report s21_matrix_tests.info

clean:
	rm -rf s21_matrix_tests test *.a *.o *.out fizz *.gc* *.info report

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-config *.h *.c
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	CK_FORK=no leaks --atExit -- ./test

rebuild:
	make clean
	make all

.PHONY:	all clean test s21_matrix.a check gcov_report
