#include "util.hpp"
#include <cstdio>

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);
    if (i < size - 1)
      printf(" ");
  }
  printf("\n");
}
