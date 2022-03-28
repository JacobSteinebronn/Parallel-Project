#!/bin/bash

g++ $1 -std=c++17 -o graph.out
echo "function compiled";

base=10000
for i in {1..10}
do
    let size=$((base*i));
    ./graph.out $size > ../input/in$i.in
    echo "input file #$i completed";
done

rm graph.out