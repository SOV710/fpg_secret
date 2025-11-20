#include "sort.hpp"
#include "util.hpp"

void SORT::selectSort(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    int min = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[min] > arr[j + 1])
        min = j;
    }

    if (min != i) {
      swap(&arr[i], &arr[min]);
    }
    if (i != size - 1)
      printArray(arr, size);
  }
}

void SORT::bubbleSort(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    bool swapped = false;

    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] < arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        swapped = true;
      }
    }

    printArray(arr, size);

    if (!swapped)
      break;
  }
}

void SORT::insertionSort(int arr[], int size) {
  for (int i = 1; i < size - 1; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;

    if (i != size - 1)
      printArray(arr, size);
  }
}
