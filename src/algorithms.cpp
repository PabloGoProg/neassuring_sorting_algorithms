#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include "fileManager.h"
using namespace std;

/**
 * @brief swap two elements of an array
 * @param a the first element
 * @param b the second element
 */
void swap(int *a, int *b);

/**
 * @brief sort an array using the bubble sort algorithm
 * @param arr the array to be sorted
 * @param n the size of the array
 */
void bubbleSort(int arr[], int n);

/**
 * @brief count the number of operations of the bubble sort algorithm (comparisson and swaps)
 * @param arr the array to be sorted
 * @param n the size of the array
 */
void countBubbleSortOps(int arr[], int n);

int partition(int arr[], int l, int h);
void quickSortIterative(int arr[], int l, int h);

/**
 * @brief measure the number of operations of the bubble sort algorithm
 * @param arr the array to be sorted
 * @param size the size of the array
 */
void testBubbleSort(int arr[], int size);

/**
 * @brief measure the execution time of the iterative quick sort algorithm
 * @param arr the array to be sorted
 * @param size the size of the array
 */
void testIterativeQuickSort(int arr[], int size);

int main()
{
  string file_names[NUM_OF_ARRAYS] = {"el1000000.txt", "el10000000.txt", "el100000000.txt"};

  int size = 10000000;
  for (int i = 0; i < NUM_OF_ARRAYS; i++)
  {
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == nullptr)
    {
      cerr << "Memory allocation failed." << endl;
      return 1;
    }

    string inputArrays = readInputData("./input/" + file_names[i]);
    formatString(inputArrays, arr, size, ",");

    // testBubbleSort(arr, size);
    // countBubbleSortOps(arr, size);

    testIterativeQuickSort(arr, size);

    system("conda run python /Users/jpgonzalez/Documents/universidad/sixth/Algorithm_Design_Course/sorting_project/src/plots_scrpit.py");

    free(arr);
    size *= 10;
  }

  return 0;
}

void testBubbleSort(int arr[], int size)
{
  for (int execs = 0; execs < 10; execs++)
  {
    int *arrCopy = (int *)malloc(size * sizeof(int));
    if (arrCopy == nullptr)
    {
      cerr << "Memory allocation failed." << endl;
      return;
    }

    for (int i = 0; i < size; i++)
    {
      arrCopy[i] = arr[i];
    }

    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    bubbleSort(arrCopy, size);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    writeInCSV("./results/bubble_time.csv", to_string(duration.count()), execs == 9);

    free(arrCopy);
  }
}

void testIterativeQuickSort(int arr[], int size)
{
  for (int execs = 0; execs < 10; execs++)
  {
    int *arrCopy = (int *)malloc(size * sizeof(int));
    if (arrCopy == nullptr)
    {
      cerr << "Memory allocation failed." << endl;
      return;
    }

    for (int i = 0; i < size; i++)
    {
      arrCopy[i] = arr[i];
    }

    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    cout << 1 << endl;
    quickSortIterative(arrCopy, 0, size - 1);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    writeInCSV("./results/quick_time.csv", to_string(duration.count()), execs == 9);

    free(arrCopy);
  }
}

void bubbleSort(int arr[], int n)
{
  int i, j; // c1 th 1

  for (i = 0; i < n - 1; i++) // c2 n

    for (j = 0; j < n - i - 1; j++) // c3 -n(n+1)/2

      if (arr[j] > arr[j + 1]) // c4 -n(n+1)/2 - 1

        swap(arr[j], arr[j + 1]); // c5 -n(n+1)/2 - 1
}

// fn = 1 + n - n(n+1)/2 - n(n+1)/2 - 1 - n(n+1)/2 - 1
// fn = 1 + n - (n2 + n)/2 - (n2 + n)/2 - 1 - (n2 + n)/2 - 1
// fn = O(n2)

void countBubbleSortOps(int arr[], int n)
{
  int i, j;
  long k = 0;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(arr[j], arr[j + 1]);
        k += 3;
      }
      k++;
    }

  writeInCSV("./results/bubble_ops.csv", to_string(k), true);
}

// A utility function to swap two elements
void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

/* This function is same in both iterative and recursive */
int partition(int arr[], int l, int h)
{
  int x = arr[h];
  int i = (l - 1);

  for (int j = l; j <= h - 1; j++)
  {
    if (arr[j] <= x)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[h]);
  return (i + 1);
}

/* A[] --> Array to be sorted,
l --> Starting index,
h --> Ending index */
void quickSortIterative(int arr[], int l, int h)
{
  // Create an auxiliary stack using dynamic memory allocation
  int *stack = (int *)malloc((h - l + 1) * sizeof(int) * 2);
  if (stack == nullptr)
  {
    cerr << "Memory allocation failed." << endl;
    return;
  }

  // initialize top of stack
  int top = -1;

  // push initial values of l and h to stack
  stack[++top] = l;
  stack[++top] = h;

  // Keep popping from stack while is not empty
  while (top >= 0)
  {
    // Pop h and l
    h = stack[top--];
    l = stack[top--];

    // Set pivot element at its correct position
    // in the sorted array
    int p = partition(arr, l, h);

    // If there are elements on the left side of the pivot,
    // then push the left side to stack
    if (p - 1 > l)
    {
      stack[++top] = l;
      stack[++top] = p - 1;
    }

    // If there are elements on the right side of the pivot,
    // then push the right side to stack
    if (p + 1 < h)
    {
      stack[++top] = p + 1;
      stack[++top] = h;
    }
  }

  // Free the memory allocated for the stack
  free(stack);
}