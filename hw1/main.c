#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include<time.h>
#include "utility.h"

#define DEF_NUM_POINTS 100000
#define DEF_NUM_ITERS 100
#define DEF_NUM_THREADS 2


int main(int argc, char **argv){
    int num_points  = DEF_NUM_POINTS;
    int num_iters   = DEF_NUM_ITERS;
    int num_threads = DEF_NUM_THREADS;
    
    
    if(argc > 1){
        num_iters = atoi(argv[2]);
        //printf("Setting number of iterations to %d\n",num_iters);
        if(argc > 2){
            num_points = atoi(argv[3]);
            //printf("Setting number of points to %d\n",num_points);
            if(argc > 3){
                num_threads = atoi(argv[4]);
                //printf("Setting number of threads to %d\n",num_threads);
            }
        }
    }

    omp_set_num_threads(num_threads);
    
    double integral = 0;
    
    if(argv[1][0]=='T'){
        clock_t begin = clock();

        for(int count=0; count<num_iters; count++){
            integral = trapezoidal(num_points);
        }

        clock_t end = clock();
        double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        double avg_time   = time_spent/num_iters;
        printf("Trapezoidal, %.6f, %d, %d, %.6f, %.6f\n", integral, num_threads, num_iters,time_spent,avg_time);
    }
    else if(argv[1][0]=='M'){
        clock_t begin = clock();

        for(int count=0; count<num_iters; count++){
            integral = trapezoidal(num_points, dx);
        }

        clock_t end = clock();
        double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        double avg_time   = time_spent/num_iters;
        printf("Monte-Carlo, %.6f, %d, %d, %.6f, %.6f\n", integral, num_threads, num_iters,time_spent,avg_time);
    }

    return 0;
}
