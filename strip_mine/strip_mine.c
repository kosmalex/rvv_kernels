
#include "stdio.h"
#include "dataset.h"
// #include "omp.h"

int res[1024];
int validd[1024];
int size = 1024;

void *sLoop(int N, int* start1, int* start2, int* res);

void print_arr(int* arr, int N){
	for(int i=0; i<N; i++){
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}

void valid(int* test, int* valid, int N){
	for(int i=0; i<N; i++){
		if(test[i] != valid[i])
			printf("[ERROR ON INDEX]: %d\n", i);
			break;
	}
}

int main(){
	for(int i=0; i<1024; i++)
		validd[i] = arr1[i] + arr2[i];

	sLoop(size, arr1, arr2, res);

	valid(res, validd, size);

	print_arr(res, 1024);
	print_arr(validd, 1024);
	
	return 0;
}
