  #include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

   MPI_Request request;
   MPI_Status status;
   int request_complete = 0; 
   int buffer = 121;
   int buffer_count = 1;

   if (rank == 0) {
      sleep(0);
     printf("I am %s, %d of %d, preparing to send ...\n", processor_name, rank, size);
     MPI_Isend(&buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
     // Here we do some work while waiting for process 1 to be ready
 MPI_Test(&request, &request_complete, &status);
     // No more work, we wait for the request to be complete if it's not the case
     if (!request_complete) {
        printf("I am %s, %d of %d, I will just wait now .. MPI_Wait() ...\n", processor_name, rank, size);
        MPI_Wait(&request, &status);
     }
   }
	
	else {
      printf("I am %s, %d of %d, will now sleep(10) ...\n", processor_name, rank, size);

      int mybuf;
      printf("I am %s, %d of %d, ready to receive ...\n", processor_name, rank, size);
      MPI_Irecv(&mybuf, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
      // Here we just wait for the message to come
  int i = 0;
     while (i<3) {
        printf("I am %s, %d of %d, sleep(10), i = %d ...\n", processor_name, rank, size, i);
        sleep(10);
        // We only test if the request is not already fulfilled
        if (!request_complete) {
           printf("I am %s, %d of %d, MPI_Wait() ...\n", processor_name, rank, size);
          
      MPI_Wait(&request, &status);
        }
        i++;
}
      printf("I am %s, %d of %d, received %d\n", processor_name, rank, size, mybuf);
   }


   // Finalize the MPI environment.
   MPI_Finalize();
}
