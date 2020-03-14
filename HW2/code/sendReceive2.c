#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
   // Initialize the MPI environment
   MPI_Init(&argc, &argv);

   int size, rank, name_len;
   char processor_name[MPI_MAX_PROCESSOR_NAME];

   // Get the number of processes
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   // Get the rank of the process
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   // Get the name of the processor
   MPI_Get_processor_name(processor_name, &name_len);

   int local_value;
   local_value = atoi(argv[rank+1]);
   printf("This is %s, rank %d out of %d processors, my local value is %d\n", processor_name, rank, size, local_value);

   int other_value;
   if (rank == 0) {
     MPI_Send(&local_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);	
     printf("Processor %s, rank %d, result = %d\n", processor_name, rank, local_value+other_value);
   }
   else {
     MPI_Recv(&other_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     MPI_Send(&local_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
     printf("Processor %s, rank %d, result = %d\n", processor_name, rank, local_value*other_value);
   }

   // Finalize the MPI environment.
   MPI_Finalize();
}

