#include <stdio.h>
#include <stdlib.h>
#include "interleaving.hpp"
#include "sort.hpp"
#include "initialize_vector.hpp"

#define DEBUG 1            // comentar esta linha quando for medir tempo
#define ARRAY_SIZE 40      // trabalho final com o valores 10.000, 100.000, 1.000.000

int main(){
    int vetor[ARRAY_SIZE];
    int i;

    initialize_vector(ARRAY_SIZE, vetor);       /* initialize array with worst case for sorting */
   

    #ifdef DEBUG
    printf("\nVetor: ");
    for (i=0 ; i<ARRAY_SIZE; i++)              /* print unsorted array */
        printf("[%03d] ", vetor[i]);
    #endif

    sort(ARRAY_SIZE, vetor);                     /* sort array */


    #ifdef DEBUG
    printf("\nVetor: ");
    for (i=0 ; i<ARRAY_SIZE; i++)                              /* print sorted array */
        printf("[%03d] ", vetor[i]);
    #endif

    return 0;
}
