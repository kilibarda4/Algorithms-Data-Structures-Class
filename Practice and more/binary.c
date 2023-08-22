#include <stdio.h>
#include <stdlib.h>

int binary_search(int Arr[], int size, int target);

int main()
{
    int Arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int size = (sizeof(Arr)/sizeof(int));
    printf("%d\n", size);
    int index = binary_search(Arr, size, 8);
    printf("Located at index %d", index);

}

int binary_search(int Arr[], int size, int target)
{
    int left, right, sus;
    left = 0;
    right = size - 1;

    while (left <= right)
    {
        sus = (left + right)/2;
        if(Arr[sus] == target) return sus;
        if(target < Arr[sus])
        {
            right = sus - 1;
        }
        else left = sus + 1;
    }
    return -1;
}