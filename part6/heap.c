#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1000

/**
 * 桁数
 * @param n 整数
 */
int digit(int n) {
  int d = 0;
  while (n > 0) {
    n /= 10;
    d++;
  }
  return d;
}

/**
 * 最大値
 */
int max(int n, int m) {
  return n < m ? m : n;
}

/**
 * ヒープから最小値を削除する
 * @param heap ヒープ
 * @param size ヒープのサイズ(のアドレス)
 */
int *deletemin(int *heap, int *size) {
  heap[0] = heap[*size - 1];
  *size -= 1;
  int n = 0;
  while (n * 2 + 1 < *size) {
    int i = n * 2 + 2 < *size && heap[n * 2 + 2] < heap[n * 2 + 1] ? 2 : 1;
    int tmp = heap[n];
    heap[n] = heap[n * 2 + i];
    heap[n * 2 + i] = tmp;
    n = n * 2 + i;
  }
  return ++heap;
}

int *insert(int x, int *heap, int *size) {
  if (*size >= MAX_SIZE) {
    printf("error: over the limit");
    return heap;
  }
  heap[*size] = x;
  int n = *size;
  *size += 1;
  while (n > 0 && heap[n] < heap[(n - 1) / 2]) {
    int tmp = heap[n];
    heap[n] = heap[(n - 1) / 2];
    heap[(n - 1) / 2] = tmp;
    n = (n - 1) / 2;
  }
  return heap;
}

/**
 * ヒープを出力する
 * @param heap ヒープ
 * @param size ヒープのサイズ
 */
void printheap(int *heap, int size) {
  int height = 1, capacity = 1;
  int maxDigit = 1;
  for (int i = 0; i < size; i++) maxDigit = max(maxDigit, digit(heap[i]));
  while (capacity < size) {
    capacity += 1 << height;
    height++;
  }
  int index = 0;
  for (int i = 0; i < height; i++) {
    printf("%*s", capacity / 2 * maxDigit, "");
    for (int j = 0; index < size && j < 1 << i; j++, index++) {
      int dig = digit(heap[index]);
      int leftSpace = (maxDigit - dig + 1) / 2 + dig;
      printf("%*d%*s", leftSpace, heap[index], capacity * maxDigit + maxDigit - leftSpace, "");
    }
    printf("\n");
    capacity /= 2;
  }
}

int main() {
  int heap[MAX_SIZE] = { 2, 7, 4, 9, 7, 4, 12, 10, 13, 11 };
  int size = 10;

  printheap(heap, size);
  deletemin(heap, &size);
  printf("\ndeletemin(heap, &size): \n");
  printheap(heap, size);
  insert(5, heap, &size);
  printf("\ninsert(5, heap, &size): \n");
  printheap(heap, size);

  return 0;
}