#!/bin/bash
# runtime comparison for parallel and sequential versions of Prim's MST


g++ $1 -std=c++17 -o seq.out
g++ -Xpreprocessor -fopenmp $2 -std=c++17 -lomp -o par.out

for i in {1..10}
do  
    start_time_seq=$(date +%s)
    ./seq.out < ../input/in$i.in > temp_seq.out
    end_time_seq=$(date +%s)
    elapsed_seq=$(($end_time_seq - $start_time_seq))
    start_time_par=$(date +%s)
    echo $elapsed_seq "s elapsed -- sequential"
    ./par.out < ../input/in$i.in > temp_par.out
    end_time_par=$(date +%s)
    elapsed_par=$(($end_time_par - $start_time_par))
    echo $elapsed_par "s elapsed -- parallel"
    diff -b temp_seq.out temp_par.out > diffed.out
    [ -s diffed.out ] && echo "Wrong output test $i"
done

rm ./seq.out
rm ./par.out
rm temp_par.out
rm temp_seq.out
rm diffed.out