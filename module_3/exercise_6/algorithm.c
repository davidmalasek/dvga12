#include <stdio.h>
#include "algorithm.h"
#include "util.h"

//
// Private
//
// Here, you might want to add some private functions that get called by
// public functions below.
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//
// Public
//
void bubble_sort(int *a, int n)
{
	int i = 0;
	int e = 0;
	
	int swapped = 0;

	while (i < n - 1) {
		e = 0;
		swapped = 0;
		while (e < n - 1 - i) { // - i because the elements on the right will be always sorted
			if (a[e] > a[e + 1]) {
				swap(&a[e], &a[e + 1]);
				swapped = 1;
			}
			e++;
		}
		i++;
		if (swapped == 0) // No swap happened, the array is sorted
			break;
	}
}

void insertion_sort(int *a, int n)
{
	int i = 1;

	while (i < n) {
		// if (a[])
	}
}

void quick_sort(int *a, int n)
{
	printf("Quick sort - To be implemented\n");
}

bool linear_search(const int *a, int n, int v)
{
	printf("Linear search - To be implemented\n");
	return false;
}

bool binary_search(const int *a, int n, int v)
{
	printf("Binary search - To be implemented\n");
	return false;
}
