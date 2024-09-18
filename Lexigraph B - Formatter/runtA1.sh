#!/bin/bash
for i in {1..9}; do
    echo "cat ../a1/tests/in0${i}.txt | python3 concord2.py | diff tests/out16.txt -"
    cat ../a1/tests/in0${i}.txt | python3 concord2.py;
    done
for i in {1..9}; do
    echo "cat ../a1/tests/in0${i}.txt | ./concord2.py | diff tests/out16.txt -"
    cat ../a1/tests/in0${i}.txt | ./concord2.py;
    done
