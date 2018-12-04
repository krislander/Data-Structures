#include "pch.h"
#include <iostream>


void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void heapify(int array[], int size, int i)
{
	//we find the left and right node of the parent i with the formula:
	// left = 2*i+1
	// right = 2*i+2
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left<size && array[left] > array[largest])
		largest = left;

	//same check for right child
	if (right<size && array[right] >array[largest])
		largest = right;

	if (largest != i) //this means if root is not he largest number in the tree
	{
		swap(&array[i], &array[largest]);
		heapify(array, size, largest);
	}
}

int partition(int array[], int low, int high)
{
	int pivot = array[high];
	int i = low - 1;

	//counter i is for when we need to switch
	//counter j is for every iteration
	for (size_t j = low; j <= high - 1; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}

void print(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << ", ";
	}
}


void heapSort(int array[], int size)
{
	//We create the Max Heap here
	for (size_t i = size / 2 - 1; i >= 0; i--)
		heapify(array, size, i);

	for (size_t i = size - 1; i >= 0; i--)
	{
		//This swaps the first and last node
		swap(&array[0], &array[i]);
		//new Max heap on reduced array without the last node
		heapify(array, i, 0);
	}
}

void quickSort(int array[], int low, int high)
{
	if (low < high)
	{
		//here we sort for the first time the numbers around the pivot
		int pivot = partition(array, low, high);

		//next couple of sorts until everything is sorted
		quickSort(array, low, pivot - 1);
		quickSort(array, pivot + 1, high);
	}
}
int main()
{
	int arr[] = { 12,11,13,5,6,7 };
	int size = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, size-1);
	std::cout << "Sorted: " << std::endl;
	print(arr, size);
}

