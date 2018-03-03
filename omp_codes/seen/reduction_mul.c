#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ARRSIZE 5

int main(int argc, char **argv)
{
	int myid, size;
	int i, val=1;
	int *A;	
	
	val = 1;
	
	//Allocate and initialize the arrays
	A = (int *)malloc(ARRSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<ARRSIZE;i++)
	{
		A[i] = i+1;
	}
	
	//print the data
	printf("\nInitial data: \n");
	for(i=0;i<ARRSIZE;i++)
	{
		printf("\t%d \n", A[i]);
	}	
	
	#pragma omp parallel for default(none) shared(A) private(myid) reduction(*:val)
	for(i=0;i<ARRSIZE;i++)
	{
		val = val * A[i];

		myid = omp_get_thread_num();
        printf("\t%d \t %d \t %d \n", i, myid,val);
	}
	
	//print the value
	printf("\nVector reduction multiplication : val = %d \n", val);
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A);
    return 0;
}
