#include <stdio.h>
#include <stdlib.h>

struct cell {
  int					 element;
  struct cell *next;
};

/**
 * 空リストを準備し、その先頭の位置を返す
 */
struct cell *newlist() {
  struct cell *init = (struct cell *) malloc(sizeof(struct cell));
  init->next = NULL;
  return init;
}

/**
 * リストinitの位置pの次に要素xを挿入する
 */
struct cell *insert(int x, struct cell *p, struct cell *init) {
  struct cell *q, *r;
  r = (struct cell *) malloc(sizeof(struct cell));
  if (p == NULL) {
    q = init->next;
    init->next = r;
  } else {
    q = p->next;
    p->next = r;
  }
  r->element = x;
  r->next = q;
  return init;
}

/**
 * リストinitの位置pの次の要素（もし存在すれば）を削除する
 */
struct cell *delete(struct cell *p, struct cell *init) {
  struct cell *q;
  if (init == NULL) {
    printf("error: list is empty.\n");
    exit(1);
  }
  if (p == NULL) {
    q = init;
    init = init->next;
    free(q);
  } else {
    if (p->next == NULL) {
      printf("error: no element to remove.\n");
      exit(1);
    } else {
      q = p->next;
      p->next = q->next;
      free(q);
    }
  }
  return init;
}

/**
 * 要素を先頭から順に出力する
 */
void printlist(struct cell *init) {
  struct cell *ptr = init;
  if (init == NULL) return;
  while (ptr->next != NULL) {
    printf("%d, ", ptr->next->element);
    ptr = ptr->next;
  }
  printf("\n");
}

/**
 * 位置pのセルの内容を返す
 */
int retrieve(struct cell *p, struct cell *init) {
  return p->element;
}

/**
 * リストinitのi番目のセルの内容を返す
 */
int find(int i, struct cell *init) {
  struct cell *ptr = init;
  int j;
  for (j = 0; j < i; j++) {
    ptr = ptr->next;
    if (ptr == NULL) return NULL;
  }
  return ptr->element;
}

/**
 * 位置pの後のセルの位置を返す
 */
struct cell *next(struct cell *p, struct cell *init) {
  return p->next;
}

/**
 * 位置pの前のセルの位置を返す
 */
struct cell *previous(struct cell *p, struct cell *init) {
  struct cell *ptr = init;
  if (init == NULL) {
    printf("error: list is empty.\n");
    exit(1);
  }
  while (ptr->next != NULL) {
    if (ptr->next == p) return ptr;
    ptr = ptr->next;
  }
  return NULL;
}

int main() {
  struct cell *list = newlist();
  insert(5, NULL, list);
  insert(4, NULL, list);
  insert(3, NULL, list);
  insert(2, NULL, list);
  insert(1, NULL, list);
  printf("printlist(list): ");
  printlist(list);
  printf("\n");
  struct cell *ptr = list->next->next->next;
  printf("retrieve(ptr, list) = %d\n", retrieve(ptr, list));
  printf("find(3, list)       = %d\n", find(3, list));
  printf("next(ptr, list)     = %d\n", next(ptr, list)->element);
  printf("previous(ptr, list) = %d\n", previous(ptr, list)->element);
  printf("\n");
  printf("delete(ptr, list)\n");
  delete(ptr, list);
  printf("printlist(list): ");
  printlist(list);
  printf("\n");
  printf("insert(8, ptr, list)\n");
  insert(8, ptr, list);
  printf("printlist(list): ");
  printlist(list);
  return 0;
}