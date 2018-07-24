//Student Name: Akshay Chandrachood
//Net ID: ******
//Student ID: ******

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char** argv) {
	
 // printf("\n*****************WELCOME TO MULTI-THREADING PROGRAM***********************\n");
    	
  int i,j,number, row_A=3,col_A=3, row_B=3, col_B=2;
  
  int A[row_A][col_A], B[row_B][col_B];
  int C[row_A][col_B];
  int SIZE_A = row_A * col_A;
  int SIZE_B = row_B * col_B;
  int SIZE_C = row_A * col_B;
 
  srand(time(NULL)); 	
		
	
  int world_rank, world_size;
  MPI_Status Stat;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  
  

  int temp1[row_A];
  int x,element;
  int rA=0,clB=0,itr,itr2;
  
  if (world_rank == 0) {
        printf("\n*********** WELCOME TO MULTI-THREADING PROHRAM *********\n\n");
	printf("\n******************* Generating Matrix A ***********\n");
	for(i=0;i<row_A;i++){
		for(j=0;j<col_A;j++){
			A[i][j] = rand()%30+1;	
		}
	}
	
	
	printf("\nPrinting the matrix in Proc 0:\n");
	for(i=0;i<row_A;i++){
		for(j=0;j<col_A;j++){
			printf(" %d ", A[i][j]);	
		}
		printf("\n");
	}	
	printf("\n\n******************* Generating Matrix B ***********\n");
	for(i=0;i<row_B;i++){
		for(j=0;j<col_B;j++){
			B[i][j] = rand()%30+1;	
		}
	}
    for(i=0;i<row_B;i++){
		for(j=0;j<col_B;j++){
			printf(" %d ", B[i][j]);	
		}
		printf("\n");
	}
	
	printf("\nSending rows to other process:\n");		

	element=0;

		for(itr=0;itr<row_A;itr++){
		MPI_Send(&B, SIZE_B, MPI_INT, itr+1, 1, MPI_COMM_WORLD);
		MPI_Send(&A, SIZE_A, MPI_INT, itr+1, 1, MPI_COMM_WORLD);
		MPI_Send(&element, 1, MPI_INT, itr+1, 1, MPI_COMM_WORLD);
		MPI_Send(&itr, 1, MPI_INT, itr+1, 1, MPI_COMM_WORLD);
		MPI_Send(&temp1, col_B, MPI_INT, itr+1, 1, MPI_COMM_WORLD);
		MPI_Send(&C, SIZE_C, MPI_INT, itr+1, 1, MPI_COMM_WORLD);
		MPI_Recv(&temp1, col_B, MPI_INT, itr+1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	
	        for(j=0;j<col_B;j++){
        	     C[itr][j] = temp1[j]; 
		  }
		}
		
		
	printf("\n\nPrinting mtrix C:\n");

	for(i=0;i<row_A;i++){
  	   for(j=0;j<col_B;j++){
		printf(" %d ",C[i][j]);
	   } printf("\n");
    }
	
  }

  else{
	printf("\n\n-----------In proc XXXX: ------------\n");  
	MPI_Recv(&B, SIZE_B, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&A, SIZE_A, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&element, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  
	MPI_Recv(&itr2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&temp1, col_B, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&C, SIZE_C, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	for(i=0;i<col_B;i++){
		temp1[i] = 0;	
	}
	
	for(i=0;i<col_B;i++){
		element = 0;
		for(x=0;x<row_B;x++){
			//printf("\n %d* %d", A[itr2][x], B[x][i]);
			element += A[itr2][x] * B[x][i];	
		}	
		//printf(" \n\nValue: %d \n\n", element);
		temp1[i] = element;
	}
	/*for(i=0;i<2;i++){
		printf(" %d ", C[itr2][i]);
	}*/
	MPI_Send(&temp1, col_B, MPI_INT, 0, 2, MPI_COMM_WORLD);

  }

  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  printf("\nRanks: %d\n", world_rank);
  MPI_Finalize();
}
