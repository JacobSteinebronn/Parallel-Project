# declare -a ns=(100 200 500 750 1000 1250 1500 1750 2000 2500 3000 3500 4000 4500 5000)
declare -a ns=(100 200 250 500 750 1000 1250 1500 2000)

printf "n,"
for i in "${ns[@]}"
do
    printf $i
    printf ","
done
echo ""

reps=1

for f in final_implementations/*.cpp
do
    g++ $f -std=c++20 -O3 -pthread
    printf ${f#*/}
    printf ","
    for i in "${ns[@]}"
    do
        big_adj/genbad.out $i
        mv ./input2.in big_adj/input.in
        start_time=$(date +%s.%3N)
        for j in {1..1}
        do
            ./a.out < big_adj/input.in 20 > /dev/null 
        done
        end_time=$(date +%s.%3N)
        elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
        ee=$(echo "scale=2 ; $elapsed / $reps" | bc )
        printf $ee
        printf ","
    done
    echo ""
done
