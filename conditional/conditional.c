#include "stdio.h"

__uint16_t a[10] = {37, 250, 78, 82, 172, 209, 47, 131, 158, 131};
__uint16_t b[10] = {27, 224, 237, 187, 160, 196, 77, 150, 125, 70};
__uint8_t  x[10] = {3, 3, 7, 0, 5, 2, 3, 6, 1, 5};
__uint16_t z[10];
__uint16_t z_as[10];

void *conditional(int N, void *a, void *b, void *x, void *z);

void print_arr(void* arr, int N){
	for(int i=0; i<N; i++){
		printf("%u ", ((unsigned short*)arr)[i]);
	}
	printf("\n\n");
}

int main(){
    for(int i=0; i<10; i++){
        z[i] =  (x[i] < 5) ? a[i] : b[i];
    }

    conditional(10, a, b, x, z_as);

    print_arr(z, 10);
    print_arr(z_as, 10);

    return 0;
}