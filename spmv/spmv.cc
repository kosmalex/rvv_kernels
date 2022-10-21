#include "stdio.h"

#include "../utils/utils.h"

const int nRows       = 6;
const int nCols       = 6;
const int nBlocks     = 5;
const int block_width = 3; 
const int NNZ         = 12;

float y_c[nCols], y_as[nCols], y_c1[nCols];

struct blk_idx{
    int row;
    int col;
};

//CSR FORMAT
int row_ptr[7]      = {0, 2, 5, 7, 8, 10, 12};
int col_idx[NNZ]    = {0, 4, 1, 2, 5, 1, 2, 3, 0, 4, 1, 5};
float data_csr[NNZ] = {1.7f, 2.3f, 3.1f, 4.2f, 3.2f, 0.3f, 5.5f, 2.3f, 3.3f, 2.9f,1.2f, 2.1f};

//CSB FORMAT
int blk_ptr[nBlocks] = {0, 5, 7, 9, 12};
int brow_idx[NNZ]    = {0, 1, 1, 2, 2, 0, 1, 1, 2, 0, 1, 2};
int bcol_idx[NNZ]    = {0, 1, 2, 1, 2, 1, 2, 0, 1, 0, 1, 2};
blk_idx elem_idx[NNZ]; //Keep the indeces in a struct array for segment load vector operations
float data_csb[NNZ]  = {1.7f, 3.1f, 4.2f, 0.3f, 5.5f, 2.3f, 3.2f, 3.3f, 1.2f,2.3f, 2.9f, 2.1f};

//DENSE VECTOR
float dvec[6] = {4.2f, 3.2f, 0.3f, 5.5f, 2.3f, 3.3f};

void spmv_c(int nRows, int* row_ptr, int* col_idx, float* data, float* x, float* y);
void spmv_csb(int nBlocks, int* blk_ptr, int* row_idx, int *col_idx, float* data, float* x, float* y);
void spmv_csb_i(int nBlocks, int* blk_ptr, blk_idx* blk_idx, float* data, float* x, float* y);

void *spmv_as(int N, int *row_ptr, int* col_idx, float* data, float* x, float* y);
void spmv(float *y);

void init_arr(float* arr, int N);
void print_arr(void* arr, int N);
int cmp(int N, float* x, float* y, float* z);

int main() {
    for(int i=0; i<NNZ; i++)
        elem_idx[i] = {brow_idx[i], bcol_idx[i]};

    init_arr(y_c, nCols);
    int t = read_cycles();
        spmv_c(nRows, row_ptr, col_idx, data_csr, dvec, y_c);
    int T = read_cycles() - t;
    printf("CSR: %d cc\n", T);
    
    // print_arr(y_c, nCols);
    printf("\n=============================\n");

    init_arr(y_c1, nCols);
    t = read_cycles();
    spmv_csb(nBlocks, blk_ptr, brow_idx, bcol_idx, data_csb, dvec, y_c1);
    int G = read_cycles() - t;
    printf("CSB: %d cc\n", G);
    // print_arr(y_c1, nCols);

    // init_arr(y_c1, nCols);
    // t = read_cycles();
    //     spmv_csb_i(nBlocks, blk_ptr, elem_idx, data_csb, dvec, y_c1);
    // int J = read_cycles() - t;
    // printf("CSB_i: %d cc\n", J);
    // print_arr(y_c1, nCols);
    
    // init_arr(y_as, nCols);
    // t = read_cycles();
    //     // spmv_as(nRows, row_ptr, col_idx, data_csr, dvec, y_as);
    // int a = read_cycles() - t;
    // printf("RVV: %d cc\n", a);

    // print_arr(y_as, nCols);

    printf("[ARRAYS ARE SAME]: %d\n", cmp(nCols, y_c, y_c1, y_c1));

    // float SpeedUp = (float)T/(float)a;
    // printf("SpeedUp: %.2f\n", SpeedUp);

    return 0;
}


void spmv_csb(int nBlocks, int* blk_ptr, int* row_idx, int *col_idx, float* data, float* x, float* y){
    for(int i=0; i<nBlocks; i++){
        for(int j=blk_ptr[i]; j<blk_ptr[i+1]; j++){
            int y_off, x_off;

            y_off = (i/2) * block_width;
            x_off = (i%2) * block_width;
            
            y[y_off+row_idx[j]] += data[j] * x[x_off + col_idx[j]];
           // printf("y[%d]: %f, data[%d]: %f, x[%d]:%f\n", y_off+row_idx[j], y[y_off+row_idx[j]], j, data[j], x_off + col_idx[j], x[x_off + col_idx[j]]);
        }
    }
}

void spmv_csb_i(int nBlocks, int* blk_ptr, blk_idx* blk_idx, float* data, float* x, float* y){
    for(int i=0; i<nBlocks; i++){
        for(int j=blk_ptr[i]; j<blk_ptr[i+1]; j++){
            for(int k=0; k<block_width*block_width;k++){
                int y_off, x_off;

                y_off = (i>>1) * block_width;
                x_off = (j&1) * block_width;

                y[y_off+blk_idx[j].row] += data[j] * x[x_off + blk_idx[j].col];
            }
        }
    }
}

void spmv_c(int nRows, int* row_ptr, int* col_idx, float* data, float* x, float* y){
  for (int i=0; i<7; i++) 
    for (int j=row_ptr[i]; j<row_ptr[i+1]; j++)
        y[i] += data[j] * x[col_idx[j]];
}

void print_arr(void* arr, int N){
    for(int i=0; i<N; i++)
        printf("%f\n", ((float*)arr)[i]);
}


void init_arr(float* arr, int N){
    for(int i=0; i<N; i++)
        arr[i] = 0.f;
}

int cmp(int N, float* x, float* y, float* z){
    for(int i=0; i<N; i++){
        if(x[i] != y[i] || y[i] != z[i] || z[i] != x[i])
            return 0;
    }

    return 1;
}

