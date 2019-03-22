// Algorithms.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

#define MAX_VALUE 100
#define ARRAY_SIZE 100

using namespace std;

void randomFill(int* array, int size, int maxVal)
{
	for (int i = 0; i < size; i++)
		array[i] = rand() % maxVal;
}

void printArray(int* array, int size)
{
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl << endl << endl;
}

class NoNumberExeption
{
};

class Sorter
{
public:
	static void bubbleSort(int* arr, int size)
	{
		bool swaped = true;

		while (swaped)
		{
			swaped = false;
			for (int i = 0; i < size - 1; i++)
				if (arr[i] > arr[i + 1])
				{
					swap(&arr[i], &arr[i + 1]);
					swaped = true;
				}
		}
	}
	static void insertionSort(int* arr, int size)
	{
		for (int i = 1; i < size; i++)
			insert(arr, &arr[i], findInsertionIndex(arr, &arr[i]));
	}

	static void selectionSort(int* arr, int size)
	{
		for (int i = 0; i < size; i++)
			swap(&arr[i], findSmallestElement(&arr[i], size - i));
	}

	static void mergeSort(int* arr, int size)
	{
		if (size <= 1)
			return;

		int sizeLeft = size / 2;
		int sizeRight = (size / 2) + size % 2;
		int* arrLeft = new int[sizeLeft];
		int* arrRight = new int[sizeRight];

		copy(arr, arr + sizeLeft - 1, arrLeft);
		copy(arr + sizeLeft, arr + size - 1, arrRight);

		mergeSort(arrLeft, sizeLeft);
		mergeSort(arrRight, sizeRight);
		merge(arr, arrLeft, sizeLeft, arrRight, sizeRight);

		delete[] arrLeft;
		delete[] arrRight;
	}

private:
	static void swap(int* elem1, int* elem2)
	{
		int buff = *elem2;
		*elem2 = *elem1;
		*elem1 = buff;
	}

	static int findInsertionIndex(int* arr, int* element)
	{
		int index = 0;
		int* curElement = element;
		while (curElement != arr)
		{
			if (*element <= *(curElement - 1))
				curElement--;
			else
			{
				index = curElement - arr;
				break;
			}
		}
		return index;
	}

	static void insert(int* arr, int* element, int position)
	{
		int value = *element;
		for (int i = element - arr; i > position; i--)
			arr[i] = arr[i - 1];
		arr[position] = value;
	}

	static int* findSmallestElement(int* arr, int size)
	{
		int* smallestElem = arr;
		for (int i = 1; i < size; i++)
			if (arr[i] < *smallestElem)
				smallestElem = &arr[i];
		return smallestElem;
	}

	static void merge(int* baseArray, int* arr1, int size1, int* arr2, int size2)
	{
		int baseSize = size1 + size2;
		for (int i = 0; i < baseSize; i++)
		{
			if (size2 == 0)
				baseArray[i] = *arr1++;
			else if (size1 == 0)
				baseArray[i] = *arr2++;
			else if (*arr1 < *arr2)
			{
				baseArray[i] = *arr1++;
				size1--;
			}
			else if (*arr2 <= *arr1)
			{
				baseArray[i] = *arr2++;
				size2--;
			}
		}
	}

	static void copy(int* arr, int* arrEnd, int* outArr)
	{
		while (arr != arrEnd)
			*outArr++ = *arr++;
		*outArr = *arr;
	}
};

int binarySearch(int* arr, int size , int value)
{
	int median = size / 2;
	if (value == arr[median])
		return median;
	else if (median == 0)
		throw NoNumberExeption();
	else if (value < arr[median])
		return binarySearch(arr, median, value);
	else if (value > arr[median])
		if(size%2)
			return median + 1 + binarySearch(arr + median + 1, median, value);
		else
			return median + 1 + binarySearch(arr + median + 1, median - 1, value);
}

char* stringReverse(const char* str)
{
	int length = strlen(str);
	while (*(str+1))
		str++;

	char* reversedString = new char[length+1];
	for (int i = 0; i < length; i++)
		reversedString[i] = *str--;

	reversedString[length] = '\0';

	return reversedString;
}

char* caesarCipher(const char* str, int key)
{
	int length = strlen(str);
	char* result = new char[length];
	key %= 26;

	for (int i = 0; i < length; i++)
	{
		char letter = str[i] + key;
		if (letter > 'z' || (str[i] >= 'A' && str[i] <= 'Z' && letter > 'Z'))
			letter -= 26;
		result[i] = letter;
	}

	result[length] = '\0';

	return result;
}

int* getFibonacciSequence(int size)
{
	int* sequence = new int[size];
	if (size == 0)
		return nullptr;
	sequence[0] = 0;
	if (size != 1)
		sequence[1] = 1;

	for (int i = 2; i < size; i++)
		sequence[i] = sequence[i - 1] + sequence[i - 2];

	return sequence;
}

int factorial(int value)
{
	if (value == 1)
		return value;
	return value * factorial(value - 1);
}

int main()
{
	srand(time(0));
	int arr[ARRAY_SIZE];

	randomFill(arr, ARRAY_SIZE, MAX_VALUE);
	printArray(arr, ARRAY_SIZE);
	Sorter::bubbleSort(arr, ARRAY_SIZE);
	printArray(arr, ARRAY_SIZE);

	randomFill(arr, ARRAY_SIZE, MAX_VALUE);
	printArray(arr, ARRAY_SIZE);
	Sorter::insertionSort(arr, ARRAY_SIZE);
	printArray(arr, ARRAY_SIZE);

	randomFill(arr, ARRAY_SIZE, MAX_VALUE);
	printArray(arr, ARRAY_SIZE);
	Sorter::selectionSort(arr, ARRAY_SIZE);
	printArray(arr, ARRAY_SIZE);

	randomFill(arr, ARRAY_SIZE, MAX_VALUE);
	printArray(arr, ARRAY_SIZE);
	Sorter::mergeSort(arr, ARRAY_SIZE);
	printArray(arr, ARRAY_SIZE);

	system("pause");
    return 0;
}

