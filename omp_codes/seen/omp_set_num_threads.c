#include<stdio.h>
#include<omp.h>

int main()
{
	int num_thds, myid;
	
	printf("\nPart1:");
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		printf("\nPart1: from thd num %d out of %d thds!", myid, num_thds);
	}

	printf("\n\nPart2:");
	omp_set_num_threads(2);
	#pragma omp parallel
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		printf("\nPart2: from thd num %d out of %d thds!", myid, num_thds);
	}
	printf("\nProgram Exit!\n");
}
