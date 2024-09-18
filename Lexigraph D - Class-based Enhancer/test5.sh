#!/bin/bash
echo "---------------------------"
echo "testing starts"
for i in {1..4}; do
    echo "---------------------------test${i}.sh---------------------------"
    bash test${i}.sh
    done
echo "---------------------------"