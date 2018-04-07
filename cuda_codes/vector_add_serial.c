#include<stdio.h>
#include<stdlib.h>

int main()
{
	int size = 200 * sizeof(int);
	int m[200], n[200], p[200];
	int i=0;

	//Initialize the vectors
	for(i=0; i<200; i++ )
	{
		m[i] = i;
		n[i] = i;
		p[i] = 0;
	}

	// Add two vectors
	for(i=0; i<200; i++ )
	{
		p[i] = m[i] + n[i];		
	}

	// print the output
	for(i=0; i<200; i++ )
	{
		printf("\t%d",p[i]);
	}	
}




