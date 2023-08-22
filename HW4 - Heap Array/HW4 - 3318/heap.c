//Nebojsa Kilibarda

#include <stdlib.h>
#include <stdio.h>

#include "heap.h"  

#define DEBUG 1
//#define DEBUG 0


//simple swap function
void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}


//calculates the index of the current max value
int idxOfMax(int* arr, int p, int left, int right, int N){
	int imv = p;
	if((left<=N-1) && (arr[left] > arr[imv]))
	{
		imv = left;
	}
	if((right<=N-1) && (arr[right] > arr[imv]))
	{
		imv = right;
	}
	return imv;
}


//creates an empty heap of size cap and returns it
struct heap_struct make_heap_empty(int cap){
	struct heap_struct heapS;
	heapS.capacity = cap;
	heapS.N = 0;
	heapS.items = calloc(cap, sizeof(int));

	return heapS;
}

//turns an array into a heap using the bottom up method
struct heap_struct make_heap(int N, int * arr){
	struct heap_struct heapS;
	heapS.capacity = N;
	heapS.N = N;
	heapS.items = arr;

	for(int p = (N-1)/2; p >= 0; p--)
	{
		sink_down(p, N, arr);
		print_heap(heapS);
	}
	return heapS;
}

//destroys the heap array
void destroy(struct heap_struct * heapP){
	if(!heapP->N)
	{
		printf("Cannot destroy an empty heap array.\n");
	}
	else
	{
		free(heapP->items);
		heapP->N = 0;
		heapP->capacity = 0;
		heapP->items = NULL;
	}
}

//prints the heap array
void print_heap(struct heap_struct heapS){
	printf("Heap: size: %d, capacity: %d\n", heapS.N, heapS.capacity);
	printf("indexes:\t");
	for(int j = 0; j < heapS.N; j++)
	{
		printf("%5d,", j);
	}
	printf("\nvalues: \t");
	for(int i = 0; i < heapS.N; i++)
	{
		printf("%5d,", heapS.items[i]);
	}
	printf("\n\n");
}

//if child is > parent, swaps their values
void swim_up(int idx, int * arr){
	while((idx > 0) && (arr[idx] > arr[(idx - 1) / 2]))
	{
		swap(&arr[idx], &arr[(idx-1)/2]);
		idx = (idx - 1) / 2;
	}
}

//if parent is not > than both children, swap with greater of the two
void sink_down(int i, int N, int * arr){
	int left = 2*i + 1;
	int right = 2*i + 2;
	int imv = idxOfMax(arr,i,left,right,N);
	while((imv != i) && (imv <= N-1))
	{
		swap(&arr[imv], &arr[i]);
		i = imv;
		left = 2*i + 1;
		right = 2*i + 2;
		imv = idxOfMax(arr, i, left, right, N);
	}
}

//inserts an item into the heap array
void add(struct heap_struct * heapP, int new_item){
	//if new item exceeds capacity, double the array capacity
	if (heapP->N == heapP->capacity)
	{
		printf("\nresizing\n");
		heapP->capacity*=2;
		heapP->items = realloc(heapP->items, heapP->capacity*sizeof(int));
	}
	int idx = heapP->N; //setting index to size before incrementing since root is at 0
	heapP->N++;
	heapP->items[idx] = new_item;
	swim_up(idx, heapP->items);
}

//returns the value of item at index 0, does not change it
int peek(struct heap_struct heapS){
	if(!heapS.items)
	{
		printf("peek: The heap array is empty.\n");
		return -1;
	}
	return heapS.items[0];
}

//removes the max item and returns its value
int poll(struct heap_struct * heapP){
	if(!heapP->N)
	{
		printf("Empty heap. no remove performed.");
		return 0;
	}
	int polled = heapP->items[0];
	heapP->N--;
	heapP->items[0] = heapP->items[heapP->N];
	sink_down(0, heapP->N, heapP->items);
	return polled;
}

