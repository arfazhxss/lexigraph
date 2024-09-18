#!/bin/bash
for i in {1..9}; do
    echo "cat tests/in0${i}.txt | python3 driver-original.py | diff tests/out0${i}.txt -"
    cat tests/in0${i}.txt | python3 driver-original.py | diff tests/out0${i}.txt -;
    done
for i in {10..16}; do
    echo "cat tests/in${i}.txt | python3 driver-original.py | diff tests/out${i}.txt -"
    cat tests/in${i}.txt | python3 driver-original.py | diff tests/out${i}.txt -;
    done
for i in {1..9}; do
    echo "cat tests/in0${i}.txt | ./driver-original.py | diff tests/out0${i}.txt -"
    cat tests/in0${i}.txt | ./driver-original.py | diff tests/out0${i}.txt -;
    done
for i in {10..16}; do
    echo "cat tests/in${i}.txt | ./driver-original.py | diff tests/out${i}.txt -"
    cat tests/in${i}.txt | ./driver-original.py | diff tests/out${i}.txt -;
    done