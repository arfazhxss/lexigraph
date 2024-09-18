#!/bin/bash
for i in {1..9}; do
    echo "cat tests/in0${i}.txt | ./concord2.py | diff tests/out0${i}.txt -"
    cat tests/in0${i}.txt | ./concord2.py | diff tests/out0${i}.txt -;
    done