#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  int					 data;
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
 * 前順で出力
 */
void preorder(struct node *n) {
  if (n == NULL) return;
  printf("%d, ", n->data);
  preorder(n->left);
  preorder(n->right);
}

/**
 * 中順で出力
 */
void inorder(struct node *n) {
  if (n == NULL) return;
  inorder(n->left);
  printf("%d, ", n->data);
  inorder(n->right);
}

/**
 * 後順で出力
 */
void postorder(struct node *n) {
  if (n == NULL) return;
  postorder(n->left);
  postorder(n->right);
  printf("%d, ", n->data);
}

/**
 * 木の高さ
 */
int height(struct node *n) {
  if (n == NULL) return 0;
  int l = height(n->left);
  int r = height(n->right);
  return 1 + (l < r ? r : l);
}

/**
 * 整数iの入ったノード（へのポインタ）
 */
struct node *locate(int i, struct node *n) {
  struct node *p = NULL;
  if (n != NULL) {
    if (n->data == i) {
      p = n;
    } else {
      p = locate(i, n->left);
      if (p == NULL) p = locate(i, n->right);
    }
  }
  return p;
}

/**
 * 整数iの入ったノードの親ノード（へのポインタ）
 */
struct node *locate_parent(int i, struct node *n) {
  struct node *p = NULL;
  if ((n->left != NULL && n->left->data == i) || (n->right != NULL && n->right->data == i)) {
    p = n;
  } else {
    if (n->left != NULL) p = locate_parent(i, n->left);
    if (p == NULL && n->right != NULL) p = locate_parent(i, n->right);
  }
  return p;
}

/**
 * 整数iの入ったノードが整数j入ったノードの子孫であるか
 */
bool is_child(int i, int j, struct node *n) {
  struct node *nj = locate(j, n);
  return locate(i, nj) != NULL;
}

/**
 * 左側に整数iの入ったノードを追加
 */
struct node *insert_left(int i, struct node *n) {
  struct node *l = newnode(i);
  n->left = l;
  return l;
}

/**
 * 右側に整数iの入ったノードを追加
 */
struct node *insert_right(int i, struct node *n) {
  struct node *r = newnode(i);
  n->right = r;
  return r;
}

int main() {

  struct node *tmp, *tree = newnode(6);
  tmp = insert_left(2, tree);
  insert_left(1, tmp);
  tmp = insert_right(4, tmp);
  insert_left(3, tmp);
  insert_right(5, tmp);
  tmp = insert_right(8, tree);
  insert_left(7, tmp);
  tmp = insert_right(10, tmp);
  insert_left(9, tmp);
  insert_right(11, tmp);

  printf("preorder(tree)\n");
  preorder(tree);
  printf("\n");
  printf("inorder(tree)\n");
  inorder(tree);
  printf("\n");
  printf("postorder(tree)\n");
  postorder(tree);
  printf("\n");
  printf("height(tree) = %d\n", height(tree));
  printf("locate(12, tree) == NULL = %d\n", locate(12, tree) == NULL);
  printf("locate_parent(7, tree)->data = %d\n", locate_parent(7, tree)->data);
  printf("is_child(5, 2, tree) = %d\n", is_child(5, 2, tree));
  printf("is_child(5, 1, tree) = %d\n", is_child(5, 1, tree));

  return 0;
}