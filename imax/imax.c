#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define SIZE 410231

float x[SIZE];
float max_val;
int idx;

void *imax_as(int N, float* array, int* idx, float* val);
void imax_c(float* array);

void gen_array(float* arr, int size, float divident, int divisor_ceil);

int main(){
    gen_array(x, SIZE, 50.65, 200);
    imax_c(x);
    imax_as(SIZE, x, &idx, &max_val);
    printf("{max: %f, idx: %d}\n", max_val, idx);
    return 0;
}

void imax_c(float* x){
    int idx = 0;
    float max = -INFINITY;
    for (int i = 0; i < SIZE; i++) {
        if (x[i] > max) {
            max = x[i];
            idx = i;
        }
    }

    printf("{max: %f, idx: %d}\n", max, idx);
}

void gen_array(float* arr, int size, float divident, int divisor_ceil){
    time_t timer;
    srand((unsigned) size);
    
    for(int i=0; i<size; i++){
        int r = rand() % divisor_ceil;
        float r_f = r ? (divident/(float)r) : 32.45;

        arr[i] = r_f;
    }
}