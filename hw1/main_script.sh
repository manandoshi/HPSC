gcc -fopenmp main.c utility.c -lm -o main
gcc -fopenmp convergance_study.c utility.c -lm -o conv

rm timing_trap.csv
rm timing_mc.csv
rm conv.csv

touch conv.csv
touch timing_trap.csv
touch timing_mc.csv

./conv > conv.csv

for i in 1 2 4 6 8
do
    counter=1
    while [ $counter -le 100 ]
    do
        ./main 'T' 1 10000 $i >> timing_trap.csv
        ((counter++))
    done
done

for i in 1 2 4 6 8
do
    counter=1
    while [ $counter -le 100 ]
    do
        ./main 'M' 1 10000 $i >> timing_mc.csv
        ((counter++))
    done
done

python report.py
