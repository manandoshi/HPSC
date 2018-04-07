mpicc -o main main.c -lm
rm conv.csv
touch conv.csv

for i in {1..30}
do
    mpirun -np 4 main 'T' $(( 12 * $i * $i)) >> conv.csv
done

for i in {1..30}
do
    counter=1
    while [ $counter -le 50 ]
    do
        mpirun -np 4 main 'M' $(( 12 * $i * $i)) >> conv.csv
        ((counter++))
    done
done
