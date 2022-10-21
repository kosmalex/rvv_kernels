#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#define SIZE 128

struct Complex{
    float real;
    float imag;
};

struct Complex a[SIZE];
struct Complex b[SIZE];
struct Complex* container[2] = {a, b};

struct Complex res_c[SIZE];
struct Complex res_as[SIZE];

void print_arr(int nElements, struct Complex* arr);
void gen_rand_flt(int nElements, int nArrays, struct Complex **carr2D, float divident, int divisor_ceil);

void *cmplxmult_as(int, struct Complex*, struct Complex*, struct Complex*);
void cmplxmult_c(int, struct Complex*, struct Complex*, struct Complex*);

int main(){
    gen_rand_flt(SIZE, 2, container, 50, 100);
    
    cmplxmult_c(SIZE, a, b, res_c);
    cmplxmult_as(SIZE, a, b, res_as);

    for(int i=0; i<SIZE; i++){
        printf("[%d] -> c:{%f, %f}, as:{%f, %f} \n", i, res_c[i].real, res_c[i].imag, res_as[i].real, res_as[i].imag);
    }
    printf("\n\n");

    return 0;
}

void print_arr(int nElements, struct Complex* arr){
    for (size_t i = 0; i < nElements; i++) {
        printf("[%d]: {real: %f, imag: %f}\n", i, arr[i].real, arr[i].imag);
    }
    printf("\n\n");
}

void gen_rand_flt(int nElements, int nArrays, struct Complex** carr2D, float divident, int divisor_ceil){    
    time_t t;
    srand((unsigned) time(&t));

    for(int j=0; j<nArrays; j++){
        for(int i=0; i<nElements; i++){
            int rand_num = rand() % divisor_ceil;
            rand_num = rand_num ? rand_num : 1;
            
            carr2D[j][i].real = divident / rand_num;

            rand_num = rand() % divisor_ceil;
            rand_num = rand_num ? rand_num : 4;
            carr2D[j][i].imag = divident / rand_num;    
        }
        
        //print_arr(nElements, carr2D[j]);
    }
}

void cmplxmult_c(int N, struct Complex* a, struct Complex* b, struct Complex* c){
    for (int i = 0; i < N; i++) {
        c[i].real = (a[i].real * b[i].real) - (a[i].imag * b[i].imag);
        c[i].imag = (a[i].imag * b[i].real) + (a[i].real * b[i].imag);
    }
}