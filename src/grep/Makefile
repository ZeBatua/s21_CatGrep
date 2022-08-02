CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
# SANITIZER = -fsanitize=address

all: clean s21_grep

s21_grep:
	$(CC) $(CFLAGS) $(SANITIZER) s21_grep.c -o s21_grep

test: s21_grep
	./test.sh

check:
	@cppcheck *.c 
	@cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../../materials/linters/cpplint.py --extension=c s21_grep.c
	$(CC) $(FLAGS) s21_grep.c $(SANITIZER) -o s21_grep
	@CK_FORK=no leaks --atExit -- ./s21_grep -e -v -l -c -i 123 qwe *.c *.txt
	@rm -rf ./CPPLINT*

valgrind:
	valgrind --leak-check=full \
     --show-leak-kinds=all \
     --track-origins=yes \
     --verbose \
     --log-file=valgrind-out.txt \
     ./s21_grep -e -v -l -c -i 123 qwe *.c *.txt

clean: 
	rm -rf s21_grep
	rm -rf s21_grep_test
	rm -rf grep