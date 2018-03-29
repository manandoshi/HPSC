#include<mpi.h>
#include<stdio.h>
#include<math.h>

#define NUM_POINTS 1200
int main(int argc, char** argv){
    //Init
    if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
        printf("MPI init failed");
        return -1;
    }
    
    
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    int np = NUM_POINTS/world_size;
    double dx = M_PI/((double)NUM_POINTS-1.0);
    double integral = 0;
    for(int i=np*world_rank;i<np*(world_rank+1); i++){
        integral += sin(i*dx)*dx;
    }
    printf("Processor %d reporting: integral = %f \n",world_rank,integral);

    MPI_Status status;
    if(world_rank == 0){
        for(int i=1; i<world_size;i++){
            double other_integral;
            MPI_Recv( &other_integral, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            integral+= other_integral;
        }
        printf("Integral: %f\n",integral);
    }

    else{
        MPI_Send( &integral, 1, MPI_DOUBLE, 0,world_rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
