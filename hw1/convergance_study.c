#include "utility.h"
#include<stdio.h>

int main(int argc, char** argv){
    char methods[2] = {'T','M'};
    
    for(int i_method = 0; i_method<2; i_method++){
        
        int num_points=2;
        
        for(int j=0; j<18; j++){
            num_points = num_points*2;
            printf("%c, %.6f, %d\n",methods[i_method],
                    integral(num_points, methods[i_method]),
                    num_points);
        }
    
    }
    return 0;

}
