#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include <time.h>

#define NUM_POINTS 100000

int main(int argc, char **argv){
    double dx = M_PI/(NUM_POINTS-1);

    clock_t begin = clock();
    double integral = 0;

    for(int count=0; count<100; count++){
        #pragma omp parallel for reduction(+:integral)
        for(int i = 1; i<NUM_POINTS-1; i++){
            integral += sin(i*dx)*dx;
        }
    }

    clock_t end = clock();

    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Computed integral(%f) in %f seconds\n",integral,time_spent);

    return 0;
}
