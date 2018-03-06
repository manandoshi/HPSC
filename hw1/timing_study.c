#include "utility.h"
#include<stdio.h>
#include<omp.h>
#include<sys/time.h>

int main(int argc, char** argv){
    char methods[2] = {'T','M'};
    struct timeval tvalBefore, tvalAfter;
    
    for(int i_method = 0; i_method<2; i_method++){

        int num_points=100000;
        for(int num_threads=4; num_threads<=4; num_threads++){
            omp_set_num_threads(num_threads);
            num_points = num_points*2;
            
            gettimeofday (&tvalBefore, NULL);
            for(int count = 0; count<10; count++){
                double val = integral(num_points, methods[i_method]);
            }
            gettimeofday (&tvalAfter, NULL);
            
            double time_usec = ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
                          +(tvalAfter.tv_usec - tvalBefore.tv_usec))/10.0;
            
            printf("%c, %.6f, %d\n",methods[i_method],
                    time_usec,
                    num_threads);
        }
    }
    return 0;
}
