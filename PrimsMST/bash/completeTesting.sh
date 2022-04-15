#!/bin/bash
# to use, run the command 'chmod +x completeTesting.sh'
# takes in 4 arguments
# arg1 - sequential program
# arg2 - parallel program
# arg3 - graph creation program
# arg4 - base number for graph creation
# arg5 - numthreads

# first, create appropriate graphs (redirect output to keep terminal clean)
./createGraphs.sh $3 $4 > graphs.out
rm graphs.out
# create file used to store program runtime
touch runtime.out
echo $4 > runtime.out
# next, run the runtime comparison, which will output runtime data to runtime.out
./runtimeComparison.sh $1 $2 $5

# create csv and print to it
touch ../csv/bench_$4.csv
python ../outToCSV.py bench_$4.csv 

rm ./runtime.out