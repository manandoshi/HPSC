#include<stdio.h>
#include<omp.h>

//Gets the total of all the myid's

int main()
{
	int myid, total;
	
	omp_set_num_threads(4);
	
	#pragma omp parallel private(myid) shared(total)
	{		
		myid = omp_get_thread_num();
		
		#pragma omp atomic update
		total += myid;		
	}
	printf("\n total = %d", total);
	printf("\nProgram Exit!\n");
}

