#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" >> log.txt

for flag in -i -v -c -l -n -e -o -s -h
do
    echo "TEST $flag"
    ./s21_grep $flag them some_text.txt >s21_grep_result
    grep $flag them some_text.txt >grep_result
    DIFF_RES="$(diff -s s21_grep_result grep_result)"
    if [ "$DIFF_RES" == "Files s21_grep_result and grep_result are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
    echo "TEST -$flag$flag2" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
done

for flag in -i -v -c -l -n -o -s -h
do
    echo "TEST $flag"
    ./s21_grep $flag -e "" -e "abc" some_text.txt >s21_grep_result
    grep $flag -e "" -e "abc" some_text.txt >grep_result
    DIFF_RES="$(diff -s s21_grep_result grep_result)"
    if [ "$DIFF_RES" == "Files s21_grep_result and grep_result are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
    echo "TEST -$flag$flag2" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
done

    echo "TEST without flags"
    ./s21_grep "" "abc" some_text.txt >s21_grep_result
    grep "" "abc" some_text.txt >grep_result
    DIFF_RES="$(diff -s s21_grep_result grep_result)"
    if [ "$DIFF_RES" == "Files s21_grep_result and grep_result are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
    echo "TEST -$flag$flag2" >> log.txt
        (( COUNTER_FAIL++ ))
    fi

for flag in i c v l h o n f s
do
    for flag2 in i c v l h o n f s
    do
    echo "TEST -$flag$flag2 -e "abc" some_text.txt"
    ./s21_grep -$flag$flag2 -e "abc" some_text.txt >s21_grep_result
    grep -$flag$flag2 -e "abc" some_text.txt >grep_result
    DIFF_RES="$(diff -s s21_grep_result grep_result)"
    if [ "$DIFF_RES" == "Files s21_grep_result and grep_result are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
    echo "TEST -$flag$flag2 -e "abc" some_text.txt" >> log.txt
        (( COUNTER_FAIL++ ))
    fi

    echo "TEST -$flag$flag2 "abc" some_text.txt"
    ./s21_grep -$flag$flag2 "abc" some_text.txt >s21_grep_result
    grep -$flag$flag2 "abc" some_text.txt >grep_result
    DIFF_RES="$(diff -s s21_grep_result grep_result)"
    if [ "$DIFF_RES" == "Files s21_grep_result and grep_result are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
    echo "TEST -$flag$flag2 "abc" some_text.txt" >> log.txt
        (( COUNTER_FAIL++ ))
    fi

    done
done

rm -rf s21_grep_result grep_result

for var in -e -i -v -c -l -n -s -h
do
  for var2 in -e -i -v -c -l -n
  do
      for var3 in -e -i -v -c -l -n
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="for s21_grep.c s21_grep.h Makefile $var $var2 $var3"
          echo "$TEST1"
          ./s21_grep $TEST1 > another_text.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s another_text.txt grep.txt)"
          if [ "$DIFF_RES" == "Files another_text.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm another_text.txt grep.txt

          TEST2="for s21_grep.c $var $var2 $var3"
          echo "$TEST2"
          ./s21_grep $TEST2 > another_text.txt
          grep $TEST2 > grep.txt
          DIFF_RES="$(diff -s another_text.txt grep.txt)"
          if [ "$DIFF_RES" == "Files another_text.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST2" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm another_text.txt grep.txt

          TEST3="-e for -e ^int s21_grep.c s21_grep.h Makefile $var $var2 $var3"
          echo "$TEST3"
          ./s21_grep $TEST3 > another_text.txt
          grep $TEST3 > grep.txt
          DIFF_RES="$(diff -s another_text.txt grep.txt)"
          if [ "$DIFF_RES" == "Files another_text.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST3" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm another_text.txt grep.txt

          TEST4="-e for -e ^int s21_grep.c $var $var2 $var3"
          echo "$TEST4"
          ./s21_grep $TEST4 > another_text.txt
          grep $TEST4 > grep.txt
          DIFF_RES="$(diff -s another_text.txt grep.txt)"
          if [ "$DIFF_RES" == "Files another_text.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST4" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm another_text.txt grep.txt

          TEST5="-e regex -e ^print s21_grep.c $var $var2 $var3 -f pattern.txt"
          echo "$TEST5"
          ./s21_grep $TEST5 > another_text.txt
          grep $TEST5 > grep.txt
          DIFF_RES="$(diff -s another_text.txt grep.txt)"
          if [ "$DIFF_RES" == "Files another_text.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST5" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm another_text.txt grep.txt

          TEST6="-e while -e void s21_grep.c Makefile $var $var2 $var3 -f pattern.txt"
          echo "$TEST6"
          ./s21_grep $TEST6 > another_text.txt
          grep $TEST6 > grep.txt
          DIFF_RES="$(diff -s another_text.txt grep.txt)"
          if [ "$DIFF_RES" == "Files another_text.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST6" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm another_text.txt grep.txt

        fi
      done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"