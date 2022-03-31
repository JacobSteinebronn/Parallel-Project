#!/bin/bash
# to use, first run the command 'chmod +x completeTesting.sh'

# takes in 2 arguments
# arg1 - numNodes
# arg2 - numThreads
# example for the included code: ./completeTesting.sh 1000 4

# create directories for input 
mkdir ../input

# first, create appropriate graphs (redirect output to keep terminal clean)
./createGraphs.sh ../weighted_graph.cpp $1 > graphs.out
rm graphs.out
# create file used to store program runtime
touch runtime.out
echo $1 > runtime.out
# next, run the runtime comparison, which will output runtime data to runtime.out
./runtimeComparison.sh ../seq_prims.cpp ../par_prims.cpp $2

# create csv and print to it
touch ../csv/bench_$2_$1.csv
python ../outToCSV.py bench_$2_$1.csv 

rm ./runtime.out
rm -r ../input
