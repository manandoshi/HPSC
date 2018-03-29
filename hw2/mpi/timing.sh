mpicc -o main main.c -lm

rm timing.csv
touch timing.csv

for i in {1..4}
do
    counter=1
    while [ $counter -le 50 ]
    do
        mpirun -np $i main 'T' 12000 >> timing.csv
        ((counter++))
    done
done

for i in {1..4}
do
    counter=1
    while [ $counter -le 50 ]
    do
        mpirun -np $i main 'M' 12000 >> timing.csv
        ((counter++))
    done
done
