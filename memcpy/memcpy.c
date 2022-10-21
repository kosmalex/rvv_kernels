#include "stdio.h"

int a[10] = {37, 250, 78, 82, 172, 209, 47, 131, 158, 131};
int b[10];

void *memcpy(void* dest, const void* src, size_t n);

int main(){
    memcpy(b, a, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", b[i]);
    }

    return 0;
}