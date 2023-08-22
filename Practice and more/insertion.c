#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], int N);
void print_arr(int arr[], int N);

int main() {
    int arr[10] = {10,9,8,7,6,5,4,3,2,1};
    print_arr(arr, 10);
    insertion_sort(arr, 10);
}

void insertion_sort(int arr[], int N) 
{
    int j, k, key;
    for( j = 1; j < N; j++)
    {
        key = arr[j];
        k = j - 1;

        while ((k >= 0) && (arr[k] > key))
        {
            arr[k+1] = arr[k];
            k = k-1;
        }
        arr[k+1] = key;
        print_arr(arr, 10);
    }
}

void print_arr(int arr[], int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}