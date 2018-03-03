#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ARRSIZE 14

main(int argc, char **argv)
{
	int num_thds, myid;
	int i, sum;
		
	omp_set_num_threads(3);
	
	#pragma omp parallel for  
	for(i=0;i<ARRSIZE;i++)
	{
		num_thds = omp_get_num_threads();		
		myid = omp_get_thread_num();
		
		printf("\nSection 1: From thd num %d out of %d thds : i = %d", myid, num_thds, i);
	}
	
	printf("\n\n");
	
	#pragma omp parallel for schedule(dynamic,3)
	for(i=0;i<ARRSIZE;i++)
	{
		num_thds = omp_get_num_threads();		
		myid = omp_get_thread_num();
		
		printf("\nSection 2: From thd num %d out of %d thds : i = %d", myid, num_thds, i);
	}
	
	printf("\nProgram exit!\n");
	
}
