#include<stdio.h>
#include<omp.h>

int main()
{
	int num_thds;
	
	omp_set_num_threads(4);
	
	#pragma omp parallel
	{
		num_thds = omp_get_num_threads();
				
		printf("\nHello World!! There are total %d thds!", num_thds);
	}
	printf("\nProgram Exit!\n");
}
