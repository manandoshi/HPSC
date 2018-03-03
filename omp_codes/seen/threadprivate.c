#include<stdio.h>
#include<omp.h>

int main()
{
	int num_thds, myid;
	
	static int val;
	
	omp_set_num_threads(4);
	
	#pragma omp threadprivate(val)
	
	#pragma omp parallel
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		val = 50;
		
		printf("\nSection 1: from thd num %d out of %d thds : val = %d", myid, num_thds, val);
	}
	
	printf("\n serial part val: %d \n",val);
	
	#pragma omp parallel private(myid)
	{		
		myid = omp_get_thread_num();
		
		val = val + myid;
	}
	
	printf("\n");
	
	#pragma omp parallel private(myid)
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		printf("\nSection 2: from thd num %d out of %d thds : val = %d", myid, num_thds, val);
	}


	printf("\nProgram Exit!\n");
}
