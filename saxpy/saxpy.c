#include "stdio.h"
#include "dataset.h"

void *saxpy(int N, float a, float *x, float *y);

void print_arr(float* arr, int N){
	for(int i=0; i<N; i++){
		printf("%f ", arr[i]);
	}
	printf("\n\n");
}

int main() {
    saxpy(128, 10.6, a, b);
    print_arr(b, 128);    
    return 0;
}