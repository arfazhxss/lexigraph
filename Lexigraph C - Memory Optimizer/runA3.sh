#!/bin/bash
echo 'Running Script'
echo '-------------------------'
gcc -g -Wall -std=c11 -o concord3 concord3.c
clang -g -Wall -std=c11 -o concord3 concord3.c
for i in {1..9}; do
    echo "cat in0${i}.txt | ./concord3"
    cat in0${i}.txt | ./concord3;
    done
for i in {10..15}; do
    echo "cat in${i}.txt | ./concord3"
    cat in${i}.txt | ./concord3;
    done
echo '-------------------------'
echo 'Done'
#rm -rf *.o
