#!/bin/bash
for i in {1..9}; do
    echo "diff out0${i}.txt _out0${i}.txt"
    diff out0${i}.txt _out0${i}.txt
    done
for i in {10..16}; do
    echo "diff out${i}.txt _out${i}.txt"
    diff out${i}.txt _out${i}.txt
    done
