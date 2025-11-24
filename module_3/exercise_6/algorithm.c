#include <stdio.h>
#include "algorithm.h"
#include "util.h"

//
// Private
//
// Here, you might want to add some private functions that get called by
// public functions below.
void swap_items(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort_range(int *a, int low, int high)
{
    int i = low;
    int e = high;
    int pivot = a[(low + high) / 2];
    int tmp;

    while (i <= e) {
        while (a[i] < pivot)
            i++;
        while (a[e] > pivot)
            e--;
        if (i <= e) {
            tmp = a[i];
            a[i] = a[e];
            a[e] = tmp;
            i++;
            e--;
        }
    }

    if (low < e)
        quick_sort_range(a, low, e);
    if (i < high)
        quick_sort_range(a, i, high);
}

//
// Public
//
void bubble_sort(int *a, int n)
{
	int i = 0;
	int e = 0;
	
	int swap_itemsped = 0;

	while (i < n - 1) {
		e = 0;
		swap_itemsped = 0;
		while (e < n - 1 - i) {
			if (a[e] > a[e + 1]) {
				swap_items(&a[e], &a[e + 1]);
				swap_itemsped = 1;
			}
			e++;
		}
		i++;
		if (swap_itemsped == 0)
			break;
	}
}

void insertion_sort(int *a, int n)
{
    int i = 1;
	int e;
	int key;

	while (i < n) {
        key = a[i];
        e = i - 1;

        while (e >= 0 && a[e] > key) {
            a[e + 1] = a[e];
            e--;
        }

        a[e + 1] = key;
		i++;
    }
}

void quick_sort(int *a, int n)
{
	if (n > 1)
		quick_sort_range(a, 0, n - 1);
}

bool linear_search(const int *a, int n, int v)
{
    int i = 0;
    while (i < n) {
        if (a[i] == v)
            return true;
        i++;
    }
    return false;
}

bool binary_search(const int *a, int n, int v)
{
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (a[mid] == v)
            return true;
        else if (a[mid] < v)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return false;
}
