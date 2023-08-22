/* 
 * Updated 2/23/2023 - Alexandra Stefan
 */

/* 
compile with -g to collect debugging info needed for Valgrind ( -lm links the math library): 
gcc -g bucket_sort.c list.c -lm

run with Valgrind:
valgrind --leak-check=full ./a.out

On some systems, but not all, you can also use the --show-leak-kinds=all flag:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "list.h"  // useful if you want to use functions from list.c

#define MAX_ARR_SIZE 10000
#define FILE_NAME_SIZE 50

void print_array(int arr[], int N);
void run1();
void bucket_sort(int * arr, int N);
struct node* insert_sorted(nodePT head, int val);

//function to sort given array via bucket sort algorithm
void bucket_sort(int * arr, int N){
	
	int min = arr[0];
	int max = arr[0];
	int index = 0;
	double dummy = 0.0;
	int counter = 0;

	//declaring array of pointers to linked lists
	//setting them all to zero
	//computing min and max in the same loop
	nodePT listArr[N];
	for(int j = 0; j < N; j++)
	{
		listArr[j] = NULL;
		if(min > arr[j])
		{
			min = arr[j];
		}
		if(max < arr[j])
		{
			max = arr[j];
		}
	}
	printf("\nBucketsort: min = %d, max = %d, N = %d buckets\n", min, max, N);
	
	//Calculating the index
	//inserting next array value into designated bucket
	for (int k = 0; k < N; k++)
	{
		dummy = ((arr[k]-min)/(1.00+max-min)*N);
		index = (int)dummy;
		printf("arr[%d]=%5d, idx = %d\n", k, arr[k], index);

		if (listArr[index] == NULL)
		{
			listArr[index] = new_node(arr[k]);
		}
		else
		{
			listArr[index] = insert_sorted(listArr[index], arr[k]);
		}
	}

	//printing each list
	for(int t = 0; t < N; t++)
	{
		printf("------list at index %d :", t);
		print_list_horiz(listArr[t]);
	}

	//copying back from listArr to original arr
	//freeing memory from linked lists
	for(int s = 0; s < N; s++)
	{
		nodePT curr = listArr[s];
		while( curr != NULL)
		{
			arr[counter] = curr->data;
			curr = curr->next;
			counter++; 
		}
		destroy_list(listArr[s]);
	}
}

//function to insert in a sorted linked list
//head of list is passed w/ value to insert
struct node* insert_sorted(nodePT head, int val)
{
	struct node* new = (struct node*)malloc(sizeof(struct node));
	new->data = val;
	new->next = NULL;

	nodePT curr = head;
	nodePT prev = NULL;

	//checking for null list first, then comparing data
	while(curr != NULL && curr->data < val)
	{
		prev = curr;
		curr = curr->next;
	}

	//the case when inserted element becomes the new head
	//the new head will be returned
	if (prev == NULL)
	{
		new->next = head;
		head = new;
		return new;
	}
	else
	{
		new->next = prev->next;
		prev->next = new;
		return head;
	}
}

void run1(){	
	char filename[FILE_NAME_SIZE];
	int arr[MAX_ARR_SIZE];
	int size = 0;
	int i = 0;

	printf("Enter file name: ");
	scanf("%s", filename);
	FILE *fp = fopen(filename, "r");
	if( fp == NULL )
	{
		printf("The file could not be opened.\n");
	}
	fscanf(fp, "%d", &size);
	while(!feof(fp))
	{
		fscanf(fp, "%d", &arr[i]);
		i++;
	}
	print_array(arr, size);
	bucket_sort(arr, size);
	print_array(arr, size);
	fclose(fp);
}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		char ch;
		scanf("%d%c",&option, &ch);  // ch is used to remove the Enter from the input buffer
 	} while (option == 1);

   return 0;
}

void print_array(int arr[], int N){
	int j;
	printf("\n array: ");
	for(j= 0; j<N; j++){
		printf("%5d,", arr[j]);
	}
	printf("\n");
}