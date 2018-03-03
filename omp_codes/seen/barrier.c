#include<stdio.h>
#include<omp.h>

int main()
{
	int num_thds, myid;
	
	omp_set_num_threads(4);
	
	#pragma omp parallel private(myid)
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		printf("\nFirst printf: %d out of %d thds!", myid, num_thds);
		
		#pragma omp barrier
		
		printf("\nSecond printf: %d out of %d thds!", myid, num_thds);
		
	}
	printf("\nProgram Exit!\n");
}

