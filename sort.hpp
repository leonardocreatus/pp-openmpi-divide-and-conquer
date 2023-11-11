// void sort(int n, int* vetor){
//     int c=0, d, troca, trocou =1;

//     while (c < (n-1) & trocou ){
//         trocou = 0;
//         for (d = 0 ; d < n - c - 1; d++) {
//             if (vetor[d] > vetor[d+1]){
//                 troca      = vetor[d];
//                 vetor[d]   = vetor[d+1];
//                 vetor[d+1] = troca;
//                 trocou = 1;
//             }
//         }
//         c++;
//     }



// }
#include <iostream>

void sort (int n, int vetor[]) {
    int k, j, aux;

    for (k = 1; k < n; k++) {
        for (j = 0; j < n - 1; j++) {
            // std::cout << "Comparando " << vetor[j] << " com " << vetor[j + 1] << std::endl;
            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }

    // std::cout << "Vetor ordenado: " << std::endl;
}