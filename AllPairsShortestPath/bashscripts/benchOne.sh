#!/bin/bash
# to use, do 'chmod +x verify.sh' once, then you can './verify.sh <problemname>'

g++ $1 -std=c++20 -O3 -pthread
for i in 100 200 500 1000 1500 2000 2500 3000 3500
do
    big_adj/gen.out $i
    mv ./input.in big_adj/input.in
    start_time=$(date +%s.%3N)
    ./a.out < big_adj/input.in > /dev/null 
    end_time=$(date +%s.%3N)
    elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
    echo $elapsed "sec. for n=$i"
done