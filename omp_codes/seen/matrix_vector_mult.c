#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define VECTORSIZE 8

main(int argc, char **argv)
{
	int myid, size;
	int i, j, sum;
	int *A, *B, *C;	
	
	//Allocate and initialize the arrays
	A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	B = (int *)malloc(VECTORSIZE*sizeof(int));
	C = (int *)malloc(VECTORSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			A[i*VECTORSIZE+j] = 1;	
		}
		B[i] = 1;
	}
	
	//print the data
	printf("\nInitial data: \n");
	printf("\nMatrix A: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", A[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	printf("\nVector B: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		printf("\t%d \n", B[i]);
	}	
	
	#pragma omp parallel for default(none) shared(A,B,C) private(j, sum)
	for(i=0;i<VECTORSIZE;i++)
	{
		sum = 0;
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = sum + A[i*VECTORSIZE+j]*B[j];	
		}
		C[i] =  sum;
	}
	
	//print the data
	printf("\nVector addition output: \n");
	printf("\nVector C: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		printf("\t%d\n", C[i]);	
	}
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
}
