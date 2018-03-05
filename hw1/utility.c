#include<omp.h>
#include<stdlib.h>
#include<math.h>

double trapezoidal(int num_points){
    double dx   = M_PI/(num_points-1);
    double integral = 0;
    #pragma omp parallel for reduction(+:integral)
    for(int i = 1; i<num_points-1; i++){
        integral += sin(i*dx)*dx;
    }
    return integral;
}

double mc(int num_points){
    double x, integral = 0;
    #pragma omp parallel for reduction(+:integral)
    for(int i = 0; i<num_points; i++){
        x = rand()*M_PI/(float)RAND_MAX;
        integral += sin(x);
    }

    integral = integral*M_PI/num_points;
    return integral;
}

double integral(int num_points, char method){
    if(method=='T'){
        return trapezoidal(num_points);
    }
    else if(method=='M'){
        return mc(num_points);
    }
    else{
        return 0.0;
    }
}
