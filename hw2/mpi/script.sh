mpicc -o main main.c -lm
rm conv.csv
touch conv.csv

for i in {1..10}
do
    mpirun -np 4 main 'T' $(( 120 * $i * $i)) >> conv.csv
done
