#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ARRSIZE 20

main(int argc, char **argv)
{
	int myid, size;
	int i, sum;
	int *A;	
	
	//Allocate and initialize the arrays
	A = (int *)malloc(ARRSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<ARRSIZE;i++)
	{
		A[i] = i;
	}
	
	//print the data
	printf("\nInitial data: \n");
	for(i=0;i<ARRSIZE;i++)
	{
		printf("\t%d \n", A[i]);
	}	
	
	#pragma omp parallel for default(none) shared(A) reduction(+:sum)
	for(i=0;i<ARRSIZE;i++)
	{
		sum = sum + A[i];
	}
	
	//print the value
	printf("\nVector reduction addition : sum = %d \n", sum);
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
}
