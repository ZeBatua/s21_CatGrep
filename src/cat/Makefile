CC = gcc #-g
CFLAGS = -Wall -Wextra -Werror
# SANITIZER = -fsanitize=address

all: clean s21_cat

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test: s21_cat
	./test.sh

check:
	@cppcheck *.c 
	@cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../../materials/linters/cpplint.py --extension=c s21_cat.c
	$(CC) $(FLAGS) s21_cat.c $(SANITIZER) -o s21_cat
	@CK_FORK=no leaks --atExit -- ./s21_cat -e -v 123 qwe *.c *.txt
	@rm -rf ./CPPLINT*

valgrind:
	valgrind --leak-check=full \
     --show-leak-kinds=all \
     --track-origins=yes \
     --verbose \
     --log-file=valgrind-out.txt \
     ./s21_cat -v -e -b -n *.txt

docker:
	sh ../../materials/build/run.sh

clean: 
	rm -rf s21_cat
	rm -rf s21_cat_test
	rm -rf cat
