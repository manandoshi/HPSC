#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ARRSIZE 20

main(int argc, char **argv)
{
	int myid, size;
	int i, val;
	int *A;	
	
	val = -1;
	
	//Allocate and initialize the arrays
	A = (int *)malloc(ARRSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<ARRSIZE;i++)
	{
		A[i] = rand()%100;
	}
	
	//print the data
	printf("\nInitial data: \n");
	for(i=0;i<ARRSIZE;i++)
	{
		printf("\t%d \n", A[i]);
	}	
	
	#pragma omp parallel for default(none) shared(A) reduction(max:val)
	for(i=0;i<ARRSIZE;i++)
	{
		if(val < A[i])
		{
			val = A[i];
		}
	}
	
	//print the value
	printf("\nMaximum value in the array : val = %d \n", val);
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
}
