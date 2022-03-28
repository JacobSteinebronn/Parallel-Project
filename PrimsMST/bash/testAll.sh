#!/bin/bash
echo "Testing data for $1";
echo "2.2" | bc
g++ -Xpreprocessor -fopenmp $1 -std=c++17 -lomp

for i in {1..10}
do
    start_time=$(date +%s.%3N)
    ./a.out < ../input/in$i.in > temp.out
    diff -b temp.out ../output/out$i.out > diffed.out
    [ -s diffed.out ] && echo "Wrong answer test $i"
    end_time=$(date +%s.%3N)
    elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
    echo "test $i " $elapsed "sec. Elapsed!"
done

rm diffed.out
rm ./a.out
rm temp.out