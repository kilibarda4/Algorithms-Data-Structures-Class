#include "hw1_student.h"  // .h extenssion, not .c

// You do not need to change this print_1D function. It is included here for 
// your convenience, in case you need to call it while debugging.
void print_1D(int sz, int * arr){
	for(int k = 0; k< sz; k++){
		printf("%8d", arr[k]);
	}
	printf("\n");
}


/* dynamically allocates an array and populates it with all values from arr 
	that are strictly smaller than thresh. 
	Returns:
		- the pointer to the dynamically allocated array.
		- NULL if all elements of arr are greater or equal to thres. In this case it does not allocate any memory, and sets content of sz_res to 0.
*/
int* get_scores_below(int thresh, int sz_arr, int * arr, int* sz_res)
{
	//used to keep track of valid numbers in arr
	int count = 0;

	//counting # of values strictly smaller than the threshold
	for(int i = 0; i < sz_arr; i++)
	{
		if(arr[i] < thresh) {
			count++;
		}
	}

	//updating size ptr
	*sz_res = count;

	if(count == 0)
	{
		return NULL;
	}

	//allocating 'count' number of integers
	int* array1D = calloc(*sz_res, sizeof(int));

	//reseting count to reuse variable
	count = 0;

	//populating dynamic 1d array w/ values that satisfy the condition
	for(int j = 0; j < sz_arr; j++)
	{
		if(arr[j] < thresh) {
			array1D[count] = arr[j];
			count++;
		}
	}

	return array1D;
}


void update_min_max(int num_rows, int num_cols, int* arr2D[], int* arr_min, int* arr_max){

	int c, r;
	*arr_min = 99999; //Making arr_min a very big number to ensure it gets updated with first value from arr2D

	//a nested loop iterating through the array and updating arr_min and arr_max
	for(r = 0; r < num_rows; r++)
	{
		for(c = 0; c < num_cols; c++)
		{
			if(*arr_min > arr2D[r][c])
			{
				*arr_min = arr2D[r][c];
			}
			else if(*arr_max < arr2D[r][c])
			{
				*arr_max = arr2D[r][c];
			}
		}
	}
}


// improve this code to print as required in the homework
void print_2D(int num_rows, int num_cols, int* arr2D[]){	
	int r,c;

	printf("\n  |");

	//printing column number
	for(int j = 0; j < num_cols; j++)
	{
		printf("%8d |", j);
	}
	
	printf("\n");
	//printing horizontal line
	for(int i = 0; i < num_cols; i++)
	{
		printf("------------");
	}
	
	printf("\n");

	for (r = 0; r<num_rows; r++)
	{
		//printing row number
		printf("%d |", r);

		for(c=0; c<num_cols; c++)
		{

			printf("%8d |", arr2D[r][c]); //updated to print | instead of ,
		}

		printf("\n");
	}	
}