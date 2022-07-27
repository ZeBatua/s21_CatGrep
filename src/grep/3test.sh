#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt

for var in -e -i -v -c -l -n
      do
        
        TEST1="$var qwe regular.txt"
        
          echo "$TEST1"
          ./s21_grep $TEST1 > 1
          grep $TEST1 > 2
          DIFF_RES="$(diff -s 1 2)"
          if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL1"
              (( COUNTER_FAIL++ ))
          fi
          rm 1 2
        
        TEST2="$var 123 regular.txt"
        
          echo "$TEST2"
          ./s21_grep $TEST2 > 1
          grep $TEST2 > 2
          DIFF_RES="$(diff -s 1 2)"
          if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL2"
              (( COUNTER_FAIL++ ))
          fi
          rm 1 2

        TEST3="$var qwe regular.txt"
        
          echo "$TEST3"
          ./s21_grep $TEST3 > 1
          grep $TEST3 > 2
          DIFF_RES="$(diff -s 1 2)"
          if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL3"
              (( COUNTER_FAIL++ ))
          fi
          rm 1 2

          TEST4="$var 123 regular.txt another_text.txt"
        
          echo "$TEST4"
          ./s21_grep $TEST4 > 1
          grep $TEST4 > 2
          DIFF_RES="$(diff -s 1 2)"
          if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL4"
              (( COUNTER_FAIL++ ))
          fi
          rm 1 2

          TEST5="$var 123 regular.txt regular.txt"
        
          echo "$TEST5!!!!!!!!!!!!!!!"
          ./s21_grep $TEST5 > 1
          grep $TEST5 > 2
          DIFF_RES="$(diff -s 1 2)"
          if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL5"
              (( COUNTER_FAIL++ ))
          fi
          rm 1 2

          TEST6="$var qwe another_text.txt poproshe.txt"
        
          echo "$TEST6"
          ./s21_grep $TEST6 > 1
          grep $TEST6 > 2
          DIFF_RES="$(diff -s 1 2)"
          if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL6"
              (( COUNTER_FAIL++ ))
          fi
          rm 1 2


          TEST7="$var qwe regular.txt another_text.txt poproshe.txt"
        
          echo "$TEST7"
          ./s21_grep $TEST7 > 1
          grep $TEST7 > 2
          DIFF_RES="$(diff -s 1 2)"
          if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "FAIL7"
              (( COUNTER_FAIL++ ))
          fi
          rm 1 2
        
    done
    for var1 in -e -i -v -c -l -n; do
    for pattern in "[0-9]" "[a-z]" "void" "21"; do
        TEST8="flag: $var1 pattern: $pattern"
        echo "$TEST8"
        ./s21_grep "$var1" "$pattern" s21_grep.c > 1
        grep "$var1" "$pattern" s21_grep.c > 2
        DIFF_RES="$(diff -s 1 2)"
        if [ "$DIFF_RES" == "Files 1 and 2 are identical" ]; then
        (( COUNTER_SUCCESS++ ))
        else
        echo "FAIL8"
        (( COUNTER_FAIL ++))
        fi
        rm 1 2
    done
    done
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"  
        
