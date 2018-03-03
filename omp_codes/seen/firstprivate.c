#include<stdio.h>
#include<omp.h>

int main()
{
	int num_thds, myid;
	int data = 10;
	
	omp_set_num_threads(4);
	
	#pragma omp parallel private(num_thds, myid, data)
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		data = data + myid;
		
		printf("\nSection 1: From thd num %d out of %d thds : data = %d", myid, num_thds, data);
	}
	
	printf("\n\ndata = %d \n", data);
	
	#pragma omp parallel private(num_thds, myid) firstprivate(data)
	{
		num_thds = omp_get_num_threads();
		
		myid = omp_get_thread_num();
		
		data = data + myid;
		
		printf("\nSection 2: From thd num %d out of %d thds : data = %d", myid, num_thds, data);
	}
	
	printf("\n\n data = %d \n", data);
	printf("\nProgram Exit!\n");
}
