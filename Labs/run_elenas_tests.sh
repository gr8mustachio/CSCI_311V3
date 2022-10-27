#!/bin/bash

echo "Enter how many tests you want to run starting from 1: "
read -r NUMBER
echo "Running $NUMBER tests..."

for i in num $NUMBER
do
    if [ $i -lt 10 ]
    then
        ./run < tests/t0"$i".in > t0"$i".my
    else 
        ./run < tests/t"$i".in > t"$i".my
    fi
done

