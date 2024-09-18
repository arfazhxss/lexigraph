#!/bin/bash
for i in {1..9}; do
    echo "./driver-new.py -in in0${i}.txt -out _out0${i}.txt"
    ./driver-new.py -in in0${i}.txt -out _out0${i}.txt;
    done
for i in {10..16}; do
    echo "./driver-new.py -in in${i}.txt -out _out${i}.txt"
    ./driver-new.py -in in${i}.txt -out _out${i}.txt;
    done
