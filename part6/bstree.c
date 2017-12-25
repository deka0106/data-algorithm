#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  int          data;
  struct node *left;
  struct node *right;
};

/**
 * 整数iの入った新しいノードを生成
 */
struct node *newnode(int i) {
  struct node *n = (struct node *) malloc(sizeof(struct node));
  n->data = i;
  n->left = NULL;
  n->right = NULL;
  return n;
}

/**
 * 整数xの入ったノードが存在するかどうか
 */
bool member(int x, struct node *n) {
  if (n == NULL) {
    return false;
  } else if (n->data == x) {
    return true;
  } else {
    return x < n->data ? member(x, n->left) : member(x, n->right);
  }
}

/**
 * 整数xの入ったノードを挿入
 */
struct node *insert(int x, struct node *n) {
  if (n == NULL) return newnode(x);
  if (x < n->data) {
    if (n->left == NULL) {
      n->left = newnode(x);
    } else {
      return insert(x, n->left);
    }
  } else if (x > n->data) {
    if (n->right == NULL) {
      n->right = newnode(x);
    } else {
      return insert(x, n->right);
    }
  }
  return n;
}

/**
 * 整数xの入ったノードを削除
 */
struct node *delete(int x, struct node *n) {
  if (n == NULL) return n;
  struct node *ret = n;
  if (x == n->data) {
    if (n->left == NULL) {
      ret = n->right;
    } else if (n->right == NULL) {
      ret = n->left;
    } else {
      struct node *tmp = n->right;
      while (tmp->left != NULL) tmp = tmp->left;
      n->data = tmp->data;
      n->right = delete(tmp->data, n->right);
    }
    free(n);
  } else if (x < n->data) {
    n->left = delete(x, n->right);
  } else {
    n->right = delete(x, n->right);
  }
  return ret;
}

/**
 * 中順で出力
 */
void inorder(struct node *n) {
  if (n == NULL) return;
  inorder(n->left);
  printf("%d ", n->data);
  inorder(n->right);
}

int main() {
  struct node *tree = newnode(0);
  for (int i = 1; i < 10; i++) {
    insert(i, tree);
  }
  inorder(tree);

  printf("\ndelete(5, tree)\n");
  delete(5, tree);
  inorder(tree);
  printf("\nmember(5, tree): %s\n", member(5, tree) ? "true" : "false");

  printf("\ninsert(5, tree)\n");
  insert(5, tree);
  inorder(tree);
  printf("\nmember(5, tree): %s\n", member(5, tree) ? "true" : "false");

  return 0;
}