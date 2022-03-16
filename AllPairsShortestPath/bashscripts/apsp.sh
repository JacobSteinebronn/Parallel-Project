#!/bin/bash
# to use, do 'chmod +x verify.sh' once, then you can './verify.sh <problemname>'
echo "Testing on APSP data for $1:";

g++ $1 -std=c++17 -O3 -pthread
start_time=$(date +%s.%3N)
for i in {1..15}
do
    ./a.out < ./apsp_normal_data/test$i.in > temp.out
    diff -b temp.out ./apsp_normal_data/test$i.out > diffed.out
    [ -s diffed.out ] && echo "Wrong answer test $i"
done
end_time=$(date +%s.%3N)
elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
echo $elapsed "sec. Elapsed!"

rm diffed.out
rm ./a.out
rm temp.out