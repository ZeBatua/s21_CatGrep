#!/bin/bash

# Test 1
./s21_cat test/test1.txt > s21_cat_test
cat test/test1.txt > cat
diff -s s21_cat_test cat

# Test 2
./s21_cat test/test1.txt test/test2.txt test/test3.txt > s21_cat_test
cat test/test1.txt test/test2.txt test/test3.txt > cat
diff -s s21_cat_test cat

# Test 3
./s21_cat -b test/test1.txt test/test2.txt > s21_cat_test
cat -b test/test1.txt test/test2.txt > cat
diff -s s21_cat_test cat

# Test 4
./s21_cat -e test/test1.txt test/test2.txt > s21_cat_test
cat -e test/test1.txt test/test2.txt > cat
diff -s s21_cat_test cat

# Test 5
./s21_cat -n test/test1.txt test/test2.txt > s21_cat_test
cat -n test/test1.txt test/test2.txt > cat
diff -s s21_cat_test cat

# Test 6
./s21_cat -s test/test1.txt test/test2.txt > s21_cat_test
cat -s test/test1.txt test/test2.txt > cat
diff -s s21_cat_test cat

# Test 7
./s21_cat -t test/test1.txt test/test2.txt > s21_cat_test
cat -t test/test1.txt test/test2.txt > cat
diff -s s21_cat_test cat

# Test 8
./s21_cat -y test/test1.txt test/test2.txt > s21_cat_test
cat -y test/test1.txt test/test2.txt > cat
diff -s s21_cat_test cat

# Test 9
./s21_cat no_file > s21_cat_test
cat no_file > cat
diff -s s21_cat_test cat
