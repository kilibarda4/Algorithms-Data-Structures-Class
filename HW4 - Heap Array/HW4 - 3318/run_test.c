#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"


int main() {
    
    char filename[50];
    FILE *fp;
    int size = 0, operations = 0, num = 0, i = 0;
    char cmd[12];

    printf("Enter the filename: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
    }

    fscanf(fp, "%d", &size);
    int *array = (int*)calloc(size, sizeof(int));

    while(i < size)
    {
        fscanf(fp, "%d", &array[i]);
        i++;
    }
    struct heap_struct heapS = make_heap(size, array); //create heap array

    fscanf(fp, "%d", &operations); //retrieve # of operations
    //retrieve each operation and call corresponding function
    //note: no error checking is performed
    for(int j = 0; j < operations; j++)
    {
        fscanf(fp, "%s", cmd);
        printf("operation number %d, string: %s\n", j+1, cmd);
        if(!strcmp(cmd, "*"))
        {
            printf("removed: %6d\n", poll(&heapS));
            print_heap(heapS);
        }
        else if(!strcmp(cmd, "p") || !strcmp(cmd, "P"))
        {
            printf("peek: %6d\n", peek(heapS));
            print_heap(heapS);
        }
        else
        {
            printf("add:  %6s\n", cmd);
            add(&heapS, atoi(cmd));
            print_heap(heapS);
        }
    }
    destroy(&heapS);
    fclose(fp);
}
