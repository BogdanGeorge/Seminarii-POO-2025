#include<iostream>

void printArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;
}

int* reverseArray(int* arr, int size)
{
	int* newReversedArray = new int[size];

	for (int i = 0; i < size; i++)
	{
		newReversedArray[i] = arr[size - i - 1];
	}

	return newReversedArray;
}

void initializeArray(int*& arr, int size)
{
	if (arr == nullptr)
	{
		arr = new int[size];
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = i + 1;
	}
}

int main()
{
	int intArr[3];
	intArr[0] = 1;
	intArr[1] = 2;
	intArr[2] = 3;

	printArray(intArr, 3);

	int* newArr = reverseArray(intArr, 3);
	printArray(newArr, 3);

	delete[] newArr;
	newArr = nullptr;

	int* a = new int[3];
	initializeArray(a, 3);
	printArray(a, 3);

	delete[] a;
	a = nullptr;

	initializeArray(a, 4);
	printArray(a, 4);

	delete[] a;
	a = nullptr;

	return 0;
}