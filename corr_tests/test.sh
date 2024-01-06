#!/bin/bash
set -v #echo on

gcc -o test0 test0.c
/usr/bin/time -l ./test0

gcc -o test1 test1.c
/usr/bin/time -l ./test1

read -p "Press any key to continue... "

./run.sh /usr/bin/time -l ./test0

./run.sh /usr/bin/time -l ./test1

read -p "Press any key to continue... "

gcc -o test2 test2.c
./run.sh /usr/bin/time -l ./test2

read -p "Press any key to continue... "

gcc -o test3 test3.c
./run.sh ./test3

read -p "Press any key to continue... "

gcc -o test4 test4.c
./run.sh ./test4

read -p "Press any key to continue... "

gcc -o test5 test5.c
./run.sh ./test5

read -p "Press any key to continue... "

gcc -o test6 test6.c -L. -lft_malloc
./test6

read -p "Press any key to continue... "

gcc -o test_bonus test_bonus.c -L. -lft_malloc
./test_bonus

rm test0 test1 test2 test3 test4 test5 test6 test_bonus