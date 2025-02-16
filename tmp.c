#include <stdio.h>

int arr[2][2] = {{1,2}, {3,4}};

int main() {
    for (int i=0; i<2; i++) {
        printf("elm: %d\n", i);
        for (int j=0; j<2; j++) {
            printf("value: %d\n", arr[i][j]);
        }
    }

    return 0;
}