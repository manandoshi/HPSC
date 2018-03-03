#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ARRSIZE 20

main(int argc, char **argv)
{
	int myid, size;
	int i;
	int *A, *B, *C;	
	
	//Allocate and initialize the arrays
	A = (int *)malloc(ARRSIZE*sizeof(int));
	B = (int *)malloc(ARRSIZE*sizeof(int));
	C = (int *)malloc(ARRSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<ARRSIZE;i++)
	{
		A[i] = i;
		B[i] = i;
	}
	
	//print the data
	printf("\nInitial data: \n");
	for(i=0;i<ARRSIZE;i++)
	{
		printf("\t%d \t %d\n", A[i], B[i]);
	}	
	
	// Perform operations in parallel
	#pragma omp parallel for default(none) shared(A,B,C)
	for(i=0;i<ARRSIZE;i++)
	{
		C[i] = A[i] + B[i];
	}
	
	//print the data
	printf("\nVector addition output: \n");
	for(i=0;i<ARRSIZE;i++)
	{
		printf("\t%d\n", C[i]);	
	}
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
}
