cls
gcc Source/AntMain.c Source/Ant.c Source/LocalSearch.c -std=c99 -o ACO -O3 -msse4
pause
ACO 1 0.75 10000 0.1 ta001.txt
pause