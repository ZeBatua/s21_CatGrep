#!/bin/bash
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="regular.txt"
echo "" > log.txt
for var in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$var 123 $TEST_FILE"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
done
for var in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 qwe $TEST_FILE"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
        fi
  done
done
# for var in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
# do
#   for var2 in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
#   do
#       for var3 in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
#       do
#         if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
#         then
#           TEST1="$var $var2 $var3 $TEST_FILE"
#           echo "$TEST1"
#           ./s21_grep $TEST1 > s21_grep.txt
#           grep $TEST1 > grep.txt
#           DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#           if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#             then
#               (( COUNTER_SUCCESS++ ))
#             else
#               echo "$TEST1" >> log.txt
#               (( COUNTER_FAIL++ ))
#           fi
#           rm s21_grep.txt grep.txt
#         fi
#       done
#   done
# done
# for var in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
# do
#   for var2 in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
#   do
#       for var3 in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
#       do
#           for var4 in -e -i -v -c -l -n -h -s -f -o #-E -T --number-nonblank --number --squeeze-blank
#           do
#             if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
#             then
#               TEST1="$var $var2 $var3 $var4 $TEST_FILE"
#               echo "$TEST1"
#               ./s21_grep $TEST1 > s21_grep.txt
#               grep $TEST1 > grep.txt
#               DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#               if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#                 then
#                   (( COUNTER_SUCCESS++ ))
#                 else
#                   echo "$TEST1" >> log.txt
#                   (( COUNTER_FAIL++ ))
#               fi
#               rm s21_grep.txt grep.txt
#             fi
#           done
#       done
#   done
# done
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"