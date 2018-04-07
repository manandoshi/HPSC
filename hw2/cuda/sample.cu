#include <stdio.h>
#include <stdlib.h>

__global__ void add(int* d_a, int* d_b, int* d_c) {
    int t = threadIdx.x;
    int index = t + blockIdx.x*blockDim.x;
    d_c[index] = d_a[index] + d_b[index];
}


int main( void) {
    const int N = 512;
    const int M = 64;
    int size = N*sizeof(int);
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;

    a = (int*)malloc(size);
    b = (int*)malloc(size);
    c = (int*)malloc(size);

    for(int i = 0; i<N; i++){
        a[i] = i;
        b[i] = 2*i;
    }

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    add<<<N/M,M>>>(d_a, d_b, d_c);

    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    for(int i = 0; i<N; i++){
        printf ("%d \t",c[i]);
    }
    printf("\n");

    return 0;
}
