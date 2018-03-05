#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include <time.h>

#define COUNT 1
#define NUM_POINTS 10000

int main(int argc, char **argv){
    double dx = M_PI/(NUM_POINTS-1);

    clock_t begin = clock();
    double x, integral = 0;

  //  for(int count=0; count<COUNT; count++){
        integral = 0;
        int myid=0;

        //#pragma omp parallel for schedule(dynamic,1250) reduction(+:integral) private(myid)
        for(int i=0; i<NUM_POINTS; i++){
            x = rand()*M_PI/(float)RAND_MAX;
            integral += sin(x);
            //myid = omp_get_thread_num();
            //printf("%f \t %d\n",x,myid);
        }
        integral = integral*M_PI/NUM_POINTS;
    //}
    
    clock_t end = clock();

    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Computed integral(%f) %d times in %f seconds\n",integral,COUNT,time_spent);

    return 0;
}
