#include <stdio.h>
#include <stdlib.h>

void my_cudasafe( cudaError_t error, char const *message)
{
	if(error!=cudaSuccess) 
	{ 
		fprintf(stderr,"ERROR: %s : %s\n",message,cudaGetErrorString(error)); 
		exit(-1); 
	}
}

__global__ void matrixMulKernel(float *md, float *nd, float *pd, int width)
{
	int tx = threadIdx.x;
	int ty = threadIdx.y;

	float Pvalue = 0;

	for(int k=0; k < width; ++k)
	{
		float Mdelement = md[ty*width+k];
		float Ndelement = nd[k*width+tx];
		Pvalue += Mdelement*Ndelement; 
	}

	pd[ty * width + tx + 10] = Pvalue;
}

void matrixmul(float *m, float *n, float *p, int width)
{
	int size = width*width*sizeof(float);
	float *md, *nd, *pd;
	

	my_cudasafe(cudaMalloc((void **)&md, size),"Cuda malloc : md");
	my_cudasafe(cudaMemcpy(md, m, size, cudaMemcpyHostToDevice),"Cuda memcopy : md");

	my_cudasafe(cudaMalloc((void **)&nd, size),"Cuda malloc : nd");
	my_cudasafe(cudaMemcpy(nd, n, size, cudaMemcpyHostToDevice),"Cuda memcopy : nd");

	my_cudasafe(cudaMalloc((void **)&pd, size),"Cuda malloc : pd");

	dim3 dimBlock(width,width);
	dim3 dimGrid(1,1);

	matrixMulKernel<<<dimGrid,dimBlock>>>(md,nd,pd,width);
	my_cudasafe(cudaGetLastError(),"Kernel invocation: matrixMulKernel");

	my_cudasafe(cudaMemcpy(p, pd, size, cudaMemcpyDeviceToHost),"Cuda memcopy : pd");
	
	my_cudasafe(cudaFree(md),"Cuda free : md");
	my_cudasafe(cudaFree(nd),"Cuda free : nd");
	my_cudasafe(cudaFree(pd),"Cuda free : pd");
}


int main()
{
	float *m, *n, *p;
	int width = 3;
	int  i = 0, j= 0;

	m = (float *)malloc(width*width*sizeof(float));
	n = (float *)malloc(width*width*sizeof(float));
	p = (float *)malloc(width*width*sizeof(float));

	for(i=0; i< width; i++)
	{
		for(j=0; j< width; j++)
		{
			m[width*i+j] = 1.00;
			n[width*i+j] = 1.00;
		}
	}

	matrixmul(m,n,p,width);

	printf("\n\n M : \n");
	for(i=0; i< width; i++)
	{
		for(j=0; j< width; j++)
		{
			printf("%f ",m[width*i+j]);
		}
		printf("\n");
	}
	printf("\n\n N : \n");
	for(i=0; i< width; i++)
	{
		for(j=0; j< width; j++)
		{
			printf("%f ",n[width*i+j]);
		}
		printf("\n");
	}
	printf("\n\n P : \n");
	for(i=0; i< width; i++)
	{
		for(j=0; j< width; j++)
		{
			printf("%f ",p[width*i+j]);
		}
		printf("\n");
	}
	return 0;
}
