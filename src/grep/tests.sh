#!/bin/bash

echo Test 1-------------------------------------------------
./s21_grep 123 some_text.txt > s21_grep_test
grep 123 some_text.txt > grep
diff -s s21_grep_test grep
echo Test 2-------------------------------------------------
./s21_grep -i rabbit test/test1.txt > s21_grep_test
grep -i rabbit test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 3-------------------------------------------------
./s21_grep -i '\(' test/test1.txt > s21_grep_test
grep -i '(' test/test1.txt > grep
diff -s s21_grep_test grep
echo Test 4-------------------------------------------------
./s21_grep -i '\(' test/test1.txt test/test2.txt > s21_grep_test
grep -i '(' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 5-------------------------------------------------
./s21_grep -i = test/test1.txt test/test2.txt > s21_grep_test
grep -i = test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 6-------------------------------------------------
./s21_grep -e 'cpp' test/test1.txt test/test2.txt > s21_grep_test
grep -e 'cpp' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 7-------------------------------------------------
./s21_grep -i zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 8-------------------------------------------------
./s21_grep -v zopa test/test1.txt test/test2.txt > s21_grep_test
grep -v zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 9-------------------------------------------------
./s21_grep -c zopa test/test1.txt test/test2.txt > s21_grep_test
grep -c zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 10-------------------------------------------------
./s21_grep -l '\(' test/test1.txt test/test2.txt > s21_grep_test
grep -l '(' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 11-------------------------------------------------
./s21_grep -n zopa test/test1.txt test/test2.txt > s21_grep_test
grep -n zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 12-------------------------------------------------
./s21_grep -i -v 12 test/test1.txt test/test2.txt > s21_grep_test
grep -i -v 12 test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 13-------------------------------------------------
./s21_grep -i -v -c zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i -v -c zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 14-------------------------------------------------
./s21_grep -i -v -c zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i -v -c zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 15-------------------------------------------------
./s21_grep -i -v -c -n zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i -v -c -n zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 17-------------------------------------------------
./s21_grep -i -v zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i -v zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 18-------------------------------------------------
./s21_grep -i -c zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i -c zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 19-------------------------------------------------
./s21_grep -i -l zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i -l zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 20-------------------------------------------------
./s21_grep -i -n zopa test/test1.txt test/test2.txt > s21_grep_test
grep -i -n zopa test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 21-------------------------------------------------
./s21_grep -v -c '=' test/test1.txt test/test2.txt > s21_grep_test
grep -v -c '=' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 22-------------------------------------------------
./s21_grep -v -l '=' test/test1.txt test/test2.txt > s21_grep_test
grep -v -l '=' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 23-------------------------------------------------
./s21_grep -v -n '=' test/test1.txt test/test2.txt > s21_grep_test
grep -v -n '=' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 24-------------------------------------------------
./s21_grep -l '=' test/test1.txt test/test2.txt > s21_grep_test
grep -l '=' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 25-------------------------------------------------
./s21_grep -c -n '=' test/test1.txt test/test2.txt > s21_grep_test
grep -c -n '=' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 26-------------------------------------------------
./s21_grep test1 test/test1.txt test/test2.txt > s21_grep_test
grep test1 test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 27-------------------------------------------------
./s21_grep -e '^test1' test/test1.txt test/test2.txt > s21_grep_test
grep -e '^test1' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 28-------------------------------------------------
./s21_grep -e 'test1$' test/test1.txt test/test2.txt > s21_grep_test
grep -e 'test1$' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 29-------------------------------------------------
./s21_grep -e '^===D$' test/test1.txt test/test2.txt > s21_grep_test
grep -e '^===D$' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 30-------------------------------------------------
./s21_grep -e '$' test/test1.txt test/test2.txt > s21_grep_test
grep -e '$' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 31-------------------------------------------------
./s21_grep -e '.s' test/test1.txt test/test2.txt > s21_grep_test
grep -e '.s' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 32-------------------------------------------------
./s21_grep -e 'te..te' test/test1.txt test/test2.txt > s21_grep_test
grep -e 'te..te' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 33-------------------------------------------------
./s21_grep -e 'zo[^p]a' test/test1.txt test/test2.txt > s21_grep_test
grep -e 'zo[^p]a' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 34-------------------------------------------------
./s21_grep -e '^[A-Z]' test/test1.txt test/test2.txt > s21_grep_test
grep -e '^[A-Z]' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 35-------------------------------------------------
./s21_grep -e 'z*opa' test/test1.txt test/test2.txt > s21_grep_test
grep -e 'z*opa' test/test1.txt test/test2.txt > grep
diff -s s21_grep_test grep
echo Test 36-------------------------------------------------
./s21_grep -o -v qwe  regular.txt  > s21_grep_test
grep -o -v qwe  regular.txt  > grep
diff -s s21_grep_test grep
