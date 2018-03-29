#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int main(int argc, char** argv){
    //Init
    if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
        printf("MPI init failed");
        return -1;
    }
    
    
    int num_points = atoi(argv[2]);
    
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

    int np = num_points/world_size;

    if(argv[1][0]=='T'){
        clock_t begin = clock();
        double dx = M_PI/((double)num_points-1.0);
        double integral = 0;
        for(int i=np*world_rank;i<np*(world_rank+1); i++){
            integral += sin(i*dx)*dx;
        }
        //printf("Processor %d reporting: integral = %f \n",world_rank,integral);

        MPI_Status status;
        if(world_rank == 0){
            for(int i=1; i<world_size;i++){
                double other_integral;
                MPI_Recv( &other_integral, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                integral+= other_integral;
            }
            clock_t end = clock();
            double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
            //double error = abs(2.0-integral);
            double error = integral > 2.0 ? integral - 2.0 : 2.0 - integral;
            printf("Trapezoidal, %.9f, %.9f,%d, %d,%.9f\n",error, integral, world_size, num_points, time_spent);
        }
        else{
            MPI_Send( &integral, 1, MPI_DOUBLE, 0,world_rank, MPI_COMM_WORLD);
        }

        MPI_Finalize();
    }

    if(argv[1][0]=='M'){
        srand(time(NULL) + world_rank);
        clock_t begin = clock();
        double integral = 0;
        for(int i=np*world_rank;i<np*(world_rank+1); i++){
            double x = rand()*M_PI/(float)RAND_MAX;
            integral += sin(x);
        }
        integral = integral*M_PI/num_points;
        //printf("Processor %d reporting: integral = %f \n",world_rank,integral);

        MPI_Status status;
        if(world_rank == 0){
            for(int i=1; i<world_size;i++){
                double other_integral;
                MPI_Recv( &other_integral, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                integral+= other_integral;
            }
            clock_t end = clock();
            double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
            double error = integral > 2.0 ? integral - 2.0 : 2.0 - integral;
            printf("Monte-Carlo, %.9f, %.9f,%d, %d,%.9f\n",error, integral, world_size, num_points, time_spent);
        }
        else{
            MPI_Send( &integral, 1, MPI_DOUBLE, 0,world_rank, MPI_COMM_WORLD);
        }

        MPI_Finalize();
    }
    return 0;
}
