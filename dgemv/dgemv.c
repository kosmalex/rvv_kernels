#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define m 10
#define n 5

float x[n], y[m], y_as[m];
float A[m][n];

void gen_data(float* vec, float mat[m][n], int N, int M, float divident, int divisor_ceil);
void init_arr(float* arr, int N);

void dgemv_c(float mat[m][n], float arr[n], float res[m]);
void *dgemv_as(int N, int M, float* mat, float* arr, float* res);

void print_mat(float mat[m][n], int N, int M);
void print_arr(float *arr, int N);

int main(){
    gen_data(x, A, n, m, 50.0f, 200);
    init_arr(y, m);
    print_mat(A, n, m);
    print_arr(x, n);

    dgemv_c(A, x, y);
    print_arr(y, m);

    dgemv_as(n, m, A, x, y_as);
    print_arr(y_as, m);

    return 0;
}

void dgemv_c(float mat[m][n], float arr[n], float res[m]){
    for(int i=0; i<m; i++)  
        for (int j=0; j<n; j++){
           // printf("{A[][]: %f, arr[]: %f}\n", A[i][j], arr[j]);
            res[i] += A[i][j] * arr[j];
        }
}

void print_mat(float mat[m][n], int N, int M){
    for (int i=0; i<M; i++)
        print_arr(mat[i], N);

    printf("\n");    
}

void print_arr(float *arr, int N){
    for(int i=0; i<N; i++)
        printf("%f ", arr[i]);
    
    printf("\n");
}


void gen_data(float* vec, float mat[m][n], int N, int M, float divident, int divisor_ceil){
    srand((unsigned)time(NULL));

    for(int i=0; i<M; i++)  
        for (int j=0; j<N; j++){
            int r_int = rand() % divisor_ceil;    
            x[j] = divident / (float)(r_int ? r_int : 0.1);

            r_int = rand() % (r_int ? r_int : 45);
            A[i][j] = divident / (float) (r_int ? r_int : 0.1);
        }
}

void init_arr(float* arr, int N){
    for (int i=0; i<N; i++) {
        arr[i] = 0.0f;
    }
    
}

