#include<stdio.h>
#include<omp.h>

int main()
{
	int num_thds, myid;
	
	omp_set_num_threads(4);
	
	#pragma omp parallel private(num_thds, myid)
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		#pragma omp master
		{
			printf("\nI am Master: %d out of %d thds!", myid, num_thds);
		}
		
		printf("\nAll: %d out of %d thds!", myid, num_thds);
		
	}
	printf("\nProgram Exit!\n");
}

