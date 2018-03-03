#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ARRSIZE 20

int main(){
    int myid;
    int i;
    int *a, *b, *c;

    a = new int[ARRSIZE];
    b = new int[ARRSIZE];
    c = new int[ARRSIZE];

    for(i=0;i<ARRSIZE;i++){
        a[i]=i;
        b[i]=ARRSIZE-i;
    }

    #pragma omp parallel for private(myid) shared(a,b,c,i)
    for(i=0;i<ARRSIZE;i++){
        c[i] = a[i] + b[i];
		myid = omp_get_thread_num();
        printf("\t%d \t %d \t %d \n", i, myid,c[i]);
    }
    return 1;
}
