#include<stdio.h>
#include<omp.h>

void foo()
{
	int i = 10;
	printf("\nHello World from foo! i = %d", 10);
}

int main()
{
	#pragma omp parallel
	{
		foo();
	}
	printf("\nProgram Exit!\n");
}
