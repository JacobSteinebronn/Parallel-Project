g++ -std=c++17 -O3 -pthread floyds_adj_parallel_k.cpp

i=0
while true
do
    start_time=$(date +%s.%3N)
    ./a.out < big_adj/input.in > temp.out
    end_time=$(date +%s.%3N)
    diff -b temp.out big_adj/output.out > diffed.out
    [ -s diffed.out ] && echo "Wrong answer!!!!! test $i"

    elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
    echo $elapsed "sec. test $i"
    i=$(($i + 1))
done
