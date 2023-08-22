#include <stdio.h>
#include <stdlib.h>


int** alloc_2D(int rows, int cols)
{
    int** arr2D = NULL;
    
    arr2D = calloc(rows, sizeof(int*));
    
    for(int r=0; r<rows; r++)
    {
        arr2D[r] = calloc(cols,sizeof(int));
    }
    
    return arr2D;
}

void free_2D(int** table, int rows)
{
    for(int r = 0; r<rows; r++)
    
    {
        free(table[r]);
    }
    
    free(table); //free this last
}

void print_2D(int** table, int rows, int cols)
{
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            printf("%d ", table[r][c]);
        }
        printf("\n");
    }
}

int main()
{
    int r = 3;
    int c = 2;
    int** arrayineed = alloc_2D(r, c);
    print_2D(arrayineed, r, c);
}