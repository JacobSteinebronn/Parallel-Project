#!/bin/bash
echo "Testing data for $1";

g++ -Xpreprocessor -fopenmp $1 -std=c++17 -lomp

for i in {1..10}
do
    start_time=$(date +%s)
    ./a.out < ../input/in$i.in > temp.out
    diff -b temp.out ../output/out$i.out > diffed.out
    [ -s diffed.out ] && echo "Wrong answer test $i"
    end_time=$(date +%s)
    elapsed=$(($end_time - $start_time))
    echo $elapsed "s elapsed!"
done

rm diffed.out
rm ./a.out
rm temp.out