The report main.tex is found at /report/main.tex, and everything needed to compile it is found in /report/

All Pairs Shortest Path:
Everything is contained in /AllPairsShortestPath/
If you want to compile a solution, you should compile with g++ -std=c++20 -O3 -pthread
To run with input, run the executable and pipe stdin/out. You can also pass in a command line arg to the executable, an integer, the number of threads (this is optional and defaults to 12). 
There's also some bash scripts in /AllPairsShortestPath/bashscripts. The most useful one is /benchAll.sh; if you run it, it will benchmark every solution in /AllPairsShortestPath/final_implementations/ (NOT the things in /temp). So if you want to compare solutions, move them from temp to final_implementations (and vice versa) and then run benchAll.sh. 