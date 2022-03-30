#!/bin/bash
# $1 = program, $2 = base
g++ $1 -std=c++17 -o graph.out
echo "function compiled";


for i in {1..10}
do
    let size=$(($2*i));
    ./graph.out $size > ../input/in$i.in
    echo "input file #$i completed";
done

rm graph.out