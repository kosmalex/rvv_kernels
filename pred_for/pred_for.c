#include "stdio.h"

char a[10] = {0, 4, 2, 4, 5, 2, 6, 1, 2, 0};
int b[10] = {6, 3, 2, 5, 1, 0, 9, 1, 7, 8};
int c[10] = {37, 250, 78, 82, 172, 209, 47, 131, 158, 131};


void *pred_for(int N, void *a, void *b, void *c);

int main(){
    pred_for(10, a, b, c);

    for (int i = 0; i < 10; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
    
    return 0;
}