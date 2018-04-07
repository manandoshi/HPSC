#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include <curand.h>
#include <curand_kernel.h>

#define TPB 512

/** Need to use this function instead of atomicAdd for double precision. Computation done in single precision(float) for now**/
__device__ double atomicAdd_double(double* address, double val)
{
    unsigned long long int* address_as_ull =
                             (unsigned long long int*)address;
    unsigned long long int old = *address_as_ull, assumed;
    do {
        assumed = old;
        old = atomicCAS(address_as_ull, assumed,
                        __double_as_longlong(val +
                               __longlong_as_double(assumed)));
    } while (assumed != old);
    return __longlong_as_double(old);
}

__global__ void trap(float *out, int N) {

    __shared__ float temp[TPB];

    temp[threadIdx.x] = 0;

    int index = threadIdx.x + blockIdx.x*blockDim.x;

    if(index>=N){
    }
    else{
        temp[threadIdx.x] = sin(M_PI*(float)index/((float)N-1));
    }

    __syncthreads();

    if(threadIdx.x == 0){
        float sum = 0;

        for(int i = 0; i<TPB; i++){
            sum += temp[i];
        }

        sum = sum*M_PI/(N-1);
        atomicAdd(out, sum);
    }
    return;
}

__global__ void mc(float *out, int N, int seed) {

    __shared__ float temp[TPB];

    temp[threadIdx.x] = 0;

    int index = threadIdx.x + blockIdx.x*blockDim.x;

    if(index>=N){
    }
    else{
        curandState_t state;
        curand_init(blockIdx.x + seed,
                    threadIdx.x,
                    0,
                    &state);

        temp[threadIdx.x] = sin(curand_uniform(&state)*M_PI);
    }

    __syncthreads();

    if(threadIdx.x == 0){
        float sum = 0;
        for(int i = 0; i<TPB; i++){
            sum += temp[i];
        }
        sum = sum*M_PI/N;
        atomicAdd(out, sum);
    }
    return;
}

int main(int argc, char** argv){

    int num_points = atoi(argv[2]);
    int num_blocks = (num_points+TPB-1)/TPB;

    if(argv[1][0]=='T'){
        clock_t begin = clock();

        float* integral;
        float* d_integral;

        cudaMalloc((void**)&d_integral, sizeof(float));
        integral = (float *)malloc(sizeof(float));

        trap<<<num_blocks,TPB>>>(d_integral, num_points);

        cudaMemcpy(integral, d_integral, sizeof(float), cudaMemcpyDeviceToHost);
        
        clock_t end = clock();
        double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        float error = *integral > 2.0 ? *integral - 2.0 : 2.0 - *integral;
        
        printf("Trapezoidal, %.12f, %.12f,%d, %d,%.12f\n",error, *integral, num_blocks, num_points, time_spent);
        
        free(integral);
        cudaFree(d_integral);
    }

    else if(argv[1][0]=='M'){
        clock_t begin = clock();

        float* integral;
        float* d_integral;

        cudaMalloc((void**)&d_integral, sizeof(float));
        integral = (float *)malloc(sizeof(float));

        mc<<<num_blocks,TPB>>>(d_integral, num_points, time(NULL));

        cudaMemcpy(integral, d_integral, sizeof(float), cudaMemcpyDeviceToHost);
        
        clock_t end = clock();
        double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        float error = *integral > 2.0 ? *integral - 2.0 : 2.0 - *integral;
        
        printf("Monte-Carlo, %.12f, %.12f,%d, %d,%.12f\n",error, *integral, num_blocks, num_points, time_spent);
        
        free(integral);
        cudaFree(d_integral);
    }
    return 0;
}
