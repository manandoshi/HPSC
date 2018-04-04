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
    int index = threadIdx.x + blockIdx.x*blockDim.x;
    if(index>=N){
        return;
    }
    __shared__ float temp[TPB];

    temp[threadIdx.x] = sin(M_PI*(float)index/((float)N-1));

    __syncthreads();
    if(threadIdx.x == 0){
        float sum = 0;
        for(int i = index; i<min(N,TPB); i++){
            sum += temp[i-index];
        }
        atomicAdd(out, sum);
    }
    return;
}


__global__ void markov(float *out, int N) {

    int index = threadIdx.x + blockIdx.x*blockDim.x;

    if(index>=N){
        return;
    }

    curandState_t state;
    curand_init(0,
                index,
                0,
                &state);

    __shared__ float temp[TPB];
    temp[index] = sin(curand_uniform(&state)*M_PI);

    __syncthreads();

    if(threadIdx.x == 0){
        float sum = 0;
        for(int i = index; i< min(N,index+TPB); i++){
            sum += temp[i]/N;
        }
        atomicAdd(out, sum);
    }
    return;
}

int main(int argc, char** argv){

    int num_points = atoi(argv[2]);
    int num_blocks = (num_points+TPB-1)/TPB;

    if(argv[1][0]=='T'){
        clock_t begin = clock();

        float integral = 1;
        float* d_integral;

        cudaMalloc((void**)&d_integral, sizeof(float));
        trap<<<num_blocks,TPB>>>(d_integral, num_points);

        cudaMemcpy(d_integral, &integral, sizeof(float), cudaMemcpyDeviceToHost);

        clock_t end = clock();
        double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        float error = integral > 2.0 ? integral - 2.0 : 2.0 - integral;

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
