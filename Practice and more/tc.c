#include <stdio.h>
#include <stdlib.h>

int main() {
    int M = 3;
    int N = 14;
    int i,k;
    for(i=0, k = 0; i<=N; i=i+k){
    printf("%d\n", k);
    for(; k<M; k=k+1)
    printf("G");
    }
}