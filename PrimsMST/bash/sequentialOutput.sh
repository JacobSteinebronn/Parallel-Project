#!/bin/bash

g++ $1 -std=c++17 -o seq.out
echo "function compiled";

for i in {1..10}
do
    start_time=$(date +%s)
    ./seq.out < ../input/in$i.in > ../output/out$i.out
    end_time=$(date +%s)
    elapsed=$(($end_time - $start_time))
    echo $elapsed "sec. Elapsed!"
done

rm seq.out