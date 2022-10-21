#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define n 4

float A[n][n]; //= {{1.0f, 2.0f}, {3.0f, 4.0f}};
float B[n][n]; //= {{1.0f, 1.5f}, {2.0f, 1.0f}};
float C_c[n][n], C_as[n][n];

void gen_data(float mat1[n][n], float mat2[n][n], float divident, int divisor_ceil);

void print_mat(float *mat, int N, int M);
void print_arr(float *arr, int N);

void dgemm_c(float A[n][n], float B[n][n], float C[n][n]);
void *dgemm_as(int N, float* A, float* B, float* C_as);

int main(){
    gen_data(A, B, 50.32, 200);

    print_mat(&A[0][0], n, n);
    print_mat(&B[0][0], n, n);

    dgemm_c(A, B, C_c);
    print_mat(&C_c[0][0], n, n);

    dgemm_as(n, &A[0][0], &B[0][0], &C_as[0][0]);
    print_mat(&C_as[0][0], n, n);

    return 0;
}

void dgemm_c(float A[n][n], float B[n][n], float C[n][n]){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void gen_data(float mat1[n][n], float mat2[n][n], float divident, int divisor_ceil){
    srand((unsigned)time(NULL));

    for(int i=0; i<n; i++)  
        for (int j=0; j<n; j++){
            int r_int = rand() % divisor_ceil;    
            mat1[i][j] = divident / (float) (r_int ? r_int : 0.1);

            r_int = rand() % (r_int ? r_int : 45);
            mat2[i][j] = divident / (float) (r_int ? r_int : 0.1);
        }
}

void print_mat(float *mat, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++)
            printf("%f ", mat[i * rows + j]);
        printf("\n");    
    }
    printf("\n");    
}