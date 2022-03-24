./big_adj/gen.out 500

g++ -std=c++20 -O3 -pthread $1
./a.out < input.in > temp1.out

g++ -std=c++20 -O3 -pthread $2
./a.out < input.in > temp2.out

diff -b temp1.out temp2.out > diffed.out
[ -s diffed.out ] && echo "WA" || echo "AC"
rm ./temp1.out
rm ./temp2.out
rm ./diffed.out
rm ./a.out