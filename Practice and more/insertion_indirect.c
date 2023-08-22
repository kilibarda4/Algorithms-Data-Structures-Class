#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], int N, int indx[]);
void print_arr(int arr[], int N, int indx[]);
void print_indx(int indx[], int size);

int main() {
    int arr[10] = {10,9,31,9,22,5,18,3,2,1};
    int indx[] = {0,1,2,3,4,5,6,7,8,9};
    // print_indx(indx, 10);
    print_arr(arr, 10, indx);
    insertion_sort(arr, 10, indx);
    // print_indx(indx,10);
    }

void insertion_sort(int arr[], int N, int indx[]) 
{
    int j, k, key;
    for( j = 1; j < N; j++)
    {
        key = indx[j];
        k = j - 1;

        while ((k >= 0) && (arr[indx[k]] > arr[key]))
        {
            indx[k+1] = indx[k];
            k = k-1;
        }
        indx[k+1] = key;
        print_arr(arr, 10, indx);
    }
}

void print_arr(int arr[], int N, int indx[])
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d ", arr[indx[i]]);
    }
    printf("\n\n");
}

//pers
void print_indx(int indx[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", indx[i]);
    }
    printf("\n");
}