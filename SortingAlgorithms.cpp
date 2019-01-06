// SortingAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>


//This is for the stopwatch to time the execution time of the Sorting Algorithms


//Helper Methods
//void merge(int array[], int l, int m, int r)
//{
//	int n1 = m - l + 1;
//	int n2 = r - m;
//	int left[n1];
//	int right[n2];
//}

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

//HELPER METHODS
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void print(int array[], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << array[i] << ", ";
	}
}

//Selection Sort - Go through and select lowest and swap with i elem
void SelectionSort(int array[], int size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		int minimumIndx = i;
		for (size_t j = i+1; j < size; j++)
		{
			if (array[j] < array[minimumIndx])
				minimumIndx = j;
		}
		swap(&array[minimumIndx], &array[i]);
	}
}

//Bubble Sort - Go through and check if j > j+1. if true swap them and continue
void BubbleSort(int array[], int size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
				swap(&array[j], &array[j + 1]);
		}
	}
}

//Insertion Sort - start from i = 1 and check the numbers before i if they are bigger than i. if true switch them.
//for i check if all elems between [0,i-1] are smaller than i
void InsertionSort(int array[], int size)
{
	int current, j;
	for (size_t i = 1; i < size; i++)
	{
		current = array[i];
		j = i - 1;


		while (j >= 0 && array[j] > current)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = current;
	}
}

//Merge Sort - divide into two subarrays, until you split into one element arrays.
//Then compare them with the neighbours and merge again into the sorted array
//void MergeSort(int array[], int left, int right)
//{
//	if (left<right)
//	{
//		int merged = left + (right - left) / 2;
//
//		MergeSort(array, left, merged);
//		MergeSort(array, merged + 1, right);
//
//		merge(array, left, merged, right);
//	}
//}

int main()
{
	int arr[] = { -5,40,30,1,2,8,45,3 };
	int size = sizeof(arr) / sizeof(arr[0]);
	InsertionSort(arr, size);
	std::cout << "Sorted: " << std::endl;
	print(arr, size);
	return 0;
}
