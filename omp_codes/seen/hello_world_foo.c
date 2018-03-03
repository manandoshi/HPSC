#include<stdio.h>
#include<omp.h>

void foo()
{
	printf("\nHello World from foo!");
}

int main()
{
	//omp_set_num_threads(4);
	#pragma omp parallel
	{
		foo();
	}
	printf("\nProgram Exit!\n");
}
