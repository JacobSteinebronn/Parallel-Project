#!/bin/bash

g++ $1 -std=c++17 -o seq.out
echo "function compiled";

for i in {1..10}
do
    ./seq.out < ../input/in$i.in > ../output/out$i.out
done

rm seq.out