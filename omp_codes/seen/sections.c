#include<stdio.h>
#include<omp.h>	

int main()
{
	int num_thds, myid;
	
	omp_set_num_threads(2);
	
	#pragma omp parallel sections
	{
		#pragma omp section 
		{
			num_thds = omp_get_num_threads();		
			myid = omp_get_thread_num();		
			printf("\nSection 1: thd num %d out of %d thds!", myid, num_thds);
		}
		#pragma omp section 
		{
			num_thds = omp_get_num_threads();		
			myid = omp_get_thread_num();		
			printf("\nSection 2: thd num %d out of %d thds!", myid, num_thds);
		}
		
		#pragma omp section 
		{
			num_thds = omp_get_num_threads();		
			myid = omp_get_thread_num();		
			printf("\nSection 3: thd num %d out of %d thds!", myid, num_thds);
		}
	}
	printf("\nProgram Exit!\n");
}
