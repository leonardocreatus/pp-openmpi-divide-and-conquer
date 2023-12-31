#include <iostream>
#include <chrono>
#include "mpi.h"
#include "interleaving.hpp"
#include "sort.hpp"
#include "initialize-vector.hpp"

// #define DEBUG 1            // comentar esta linha quando for medir tempo
#define ARRAY_SIZE 1000000 // trabalho final com o valores 10.000, 100.000, 1.000.000

int main(int argc, char* argv[]){

    auto start = std::chrono::high_resolution_clock::now();

    MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if(size < 3) {
        std::cout << "Error: must have at least 3 processes!" << std::endl;
        MPI_Finalize();
        return 0;
    }
	const int delta = ARRAY_SIZE / (size / 2 + 1);

    int father_id = rank == 0 ? -1 : (rank - 1) / 2;
    bool is_leaf = 2 * rank + 1 >= size;
    int left_child_id = 2 * rank + 1;
    int right_child_id = 2 * rank + 2;
    int size_vector;
    int *vector;
    
    vector = new int[ARRAY_SIZE];

    if( rank != 0){
        MPI_Recv(vector, ARRAY_SIZE, MPI_INT, father_id, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &size_vector);
    }else {
        size_vector = ARRAY_SIZE;
        initialize_vector(size_vector, vector);
    }

    if(size_vector <= delta){
        sort(size_vector, vector); 
    }else {

        MPI_Send(&vector[0], size_vector/2, MPI_INT, left_child_id, 0, MPI_COMM_WORLD);
        MPI_Send(&vector[size_vector/2], size_vector/2, MPI_INT, right_child_id, 0, MPI_COMM_WORLD);


        MPI_Recv(&vector[0], size_vector/2, MPI_INT, left_child_id, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&vector[size_vector/2], size_vector/2, MPI_INT, right_child_id, 0, MPI_COMM_WORLD, &status);

        vector = interleaving(vector, size_vector);
    }

    if(rank != 0){
        MPI_Send(vector, size_vector, MPI_INT, father_id, 0, MPI_COMM_WORLD);
    }

    
    if(rank == 0){
        #ifdef DEBUG
            printf("\nVetor: ");
            for (int i=0 ; i< ARRAY_SIZE; i++){
                printf("[%03d] ", vector[i]);
            }
        #endif
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms = end - start;
        std::cout << "time: " << ms.count() << "ms" << std::endl;
    }
    

    MPI_Finalize();
    return 0;
}
