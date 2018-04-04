#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include <curand.h>
#include <curand_kernel.h>

#define TPB 512

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


__global__ void trap(double *out, int *N) {
    int index = threadIdx.x + blockIdx.x*blockDim.x;
    if(index>=*N){
        return;
    }
    __shared__ double temp[TPB];

    temp[index] = sin(M_PI*(double)index/((double)*N-1));

    __syncthreads();
    if(threadIdx.x == 0){
        double sum = 0;
        for(int i = index; i< min(*N,index+TPB); i++){
            sum += temp[i];
        }
        atomicAdd_double(out, sum);
    }
    return;
}



int main(int argc, char** argv){

    int num_points = atoi(argv[2]);

    int num_blocks = num_points/TPB + 1;


    if(argv[1][0]=='T'){
        clock_t begin = clock();

        double integral;
        double* d_integral;
        int* d_N;

        cudaMalloc((void**)&d_N, sizeof(int));
        cudaMalloc((void**)&d_integral, sizeof(double));
        
        cudaMemcpy(d_N, &num_points, sizeof(int), cudaMemcpyHostToDevice);

        trap<<<num_blocks,TPB>>>(d_integral, d_N);

        cudaMemcpy(&integral, d_integral, sizeof(double), cudaMemcpyDeviceToHost);

        clock_t end = clock();
        double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        double error = integral > 2.0 ? integral - 2.0 : 2.0 - integral;

        printf("Trapezoidal, %.9f, %.9f,%d, %d,%.9f\n",error, integral, num_blocks, num_points, time_spent);
    }
    /*
    else if(argv[1][0]=='M'){
        srand(time(NULL) + world_rank);
        clock_t begin = clock();
        double integral = 0;
        for(int i=np*world_rank;i<np*(world_rank+1); i++){
            double x = rand()*M_PI/(double)RAND_MAX;
            integral += sin(x);
        }
        integral = integral*M_PI/num_points;
        //printf("Processor %d reporting: integral = %f \n",world_rank,integral);

        MPI_Status status;
        if(world_rank == 0){
            for(int i=1; i<world_size;i++){
                double other_integral;
                MPI_Recv( &other_integral, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                integral+= other_integral;
            }
            clock_t end = clock();
            double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
            double error = integral > 2.0 ? integral - 2.0 : 2.0 - integral;
            printf("Monte-Carlo, %.9f, %.9f,%d, %d,%.9f\n",error, integral, world_size, num_points, time_spent);
        }
        else{
            MPI_Send( &integral, 1, MPI_DOUBLE, 0,world_rank, MPI_COMM_WORLD);
        }

        MPI_Finalize();
    }
    */
    return 0;
}
