#!/bin/bash

# # Test_1
# ./s21_cat test/test1.txt > s21_cat_test
# cat test/test1.txt > cat
# diff -s s21_cat_test cat

# # Test_2
# ./s21_cat test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
# cat test/test1.txt test/test2.txt test/test3.txt > cat
# diff -s s21_cat_test cat

# # Test_3
# ./s21_cat -b test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
# cat -b test/test1.txt test/test2.txt test/test3.txt > cat
# diff -s s21_cat_test cat

# # Test_4
# ./s21_cat -e -v test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
# cat -e -v test/test1.txt test/test2.txt test/test3.txt > cat
# diff -s s21_cat_test cat

# # Test_5
# ./s21_cat -n test/test1.txt test/test2.txt > s21_cat_test
# cat -n test/test1.txt test/test2.txt > cat
# diff -s s21_cat_test cat

# Test_6
./s21_cat -s test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -s test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_7
./s21_cat -t -v test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -t -v test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_8
./s21_cat -v test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -v test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_9
./s21_cat -E test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -e test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_10
./s21_cat --number test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -n test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_11
./s21_cat --squeeze-blank test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -s test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_12
./s21_cat -E test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -e test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_13
./s21_cat -T test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -t test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_14
./s21_cat --number-nonblank test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -b test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test_15
./s21_cat -- test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat -- test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat