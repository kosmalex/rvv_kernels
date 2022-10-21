#include "stdio.h"
#include "stdlib.h"
#include "dataset.h"

#include "utils.h"

#define MAX(a, b) (a > b) ? a : b

int row_ptrC[R+1];
int col_idxC[NNZA + NNZB];
float dataC[NNZA + NNZB];
int size = 0;

void print_mat(int *row_ptrC, int *col_idxC, float *dataC);

void spma_c(int *row_ptrC, int *col_idxC, float *dataC); // C = A + B

void spma(int *row_ptrC, int *col_idxC, float *dataC); // C = A + B
void *spma_as(int AVL, float *data, int *idx, float *dataC, int* idxC, int* l);

int main(){
    int t = read_cycles();
    spma_c(row_ptrC, col_idxC, dataC);
    t = read_cycles() - t;

    // print_mat(row_ptrC, col_idxC, dataC);
    printf("\nC: %d", t);

    int T = read_cycles();
    spma(row_ptrC, col_idxC, dataC);
    T = read_cycles() - T;

    // print_mat(row_ptrC, col_idxC, dataC);
    printf("\nRVV: %d\n", T);
    
    printf("SpeedUp: %f\n", (float)t/(float)T);

    return 0;
}

void spma(int *row_ptrC, int *col_idxC, float *dataC){ 
    int l = 0;
    row_ptrC[0] = 0;

    for(int i=0; i<R; i++){
        int j=row_ptrA[i], k=row_ptrB[i];

        row_ptrC[i+1] = MAX(row_ptrA[i+1], row_ptrB[i+1]);

        for(; j<row_ptrA[i+1] & k<row_ptrB[i+1]; l++){
            if(col_idxA[j] == col_idxB[k]){
                dataC[l] = dataA[j] + dataB[k];
                col_idxC[l] = col_idxA[j];
                j++, k++;
            } 
            else if (col_idxA[j] > col_idxB[k]){
                dataC[l] = dataB[k];
                col_idxC[l] = col_idxB[k];
                k++;
            }
            else {
                dataC[l] = dataA[j];
                col_idxC[l] = col_idxA[j];
                j++;
            }
        }

        if(row_ptrA[i+1]-j != 0)
            spma_as(row_ptrA[i+1]-j, &dataA[j], &col_idxA[j], &dataC[l], &col_idxC[l], &l);
        else if(row_ptrB[i+1]-k != 0)
            spma_as(row_ptrB[i+1]-k, &dataB[k], &col_idxB[k], &dataC[l], &col_idxC[l], &l);
    
        size = l;
    }
}

void spma_c(int *row_ptrC, int *col_idxC, float *dataC){ 
    int l = 0;
    row_ptrC[0] = 0;

    for(int i=0; i<R; i++){
        int j=row_ptrA[i], k=row_ptrB[i];

        row_ptrC[i+1] = MAX(row_ptrA[i+1], row_ptrB[i+1]);

        for(; j<row_ptrA[i+1] & k<row_ptrB[i+1]; l++){
            if(col_idxA[j] == col_idxB[k]){
                dataC[l] = dataA[j] + dataB[k];
                col_idxC[l] = col_idxA[j];
                j++, k++;
            } 
            else if (col_idxA[j] > col_idxB[k]){
                dataC[l] = dataB[k];
                col_idxC[l] = col_idxB[k];
                k++;
            }
            else {
                dataC[l] = dataA[j];
                col_idxC[l] = col_idxA[j];
                j++;
            }
        }
       
        for(;j<row_ptrA[i+1];j++, l++){
            dataC[l] = dataA[j];
            col_idxC[l] = col_idxA[j];
        }

        for(;k<row_ptrB[i+1];k++, l++){
            dataC[l] = dataB[k];
            col_idxC[l] = col_idxB[k];
        }
    
        size = l;
    }
}

void print_mat(int *row_ptrC, int *col_idxC, float *dataC){
    for(int i=0; i<size; i++)
        printf("{ptr: %d, idx: %d, ele: %f}\n", row_ptrC[i], col_idxC[i], dataC[i]);
    printf("\n\n");
}

