#include <stdio.h>
#include <stdlib.h>

#define N      8
#define Q_SIZE 100

int G[N][N] = {
//  0  1  2  3  4  5  6  7
  { 0, 1, 0, 0, 0, 1, 1, 1 }, // 0
  { 0, 0, 1, 1, 0, 1, 0, 0 }, // 1
  { 0, 0, 0, 1, 1, 0, 0, 0 }, // 2
  { 0, 0, 0, 0, 0, 0, 0, 0 }, // 3
  { 0, 0, 0, 0, 0, 0, 0, 0 }, // 4
  { 0, 0, 0, 0, 0, 0, 0, 0 }, // 5
  { 0, 0, 0, 0, 0, 0, 0, 0 }, // 6
  { 0, 0, 0, 0, 0, 0, 1, 0 }  // 7
};

int visited[N];

/**
 * 待ち行列(キュー)
 */
struct queue {
  int first, last;
  int array[Q_SIZE];
};

/**
 * 待ち行列(キュー)作成
 */
struct queue *new_queue() {
  struct queue *q = (struct queue *) malloc(sizeof(struct queue));
  for (int i = 0; i < Q_SIZE; i++) q->array[i] = 0;
  q->first = 0;
  q->last = 0;
}

/**
 * 待ち行列qが空であるかどうか
 */
int is_empty(struct queue *q) {
  return q->first == q->last;
}

/**
 * 待ち行列qの末尾に要素vを追加
 */
void offer(int v, struct queue *q) {
  if ((q->last + 1) % Q_SIZE == q->first) {
    printf("error: q is full.\n");
    return;
  }
  q->array[q->last] = v;
  q->last = (q->last + 1) % Q_SIZE;
}

/**
 * 待ち行列qの最初の要素を取得及び削除
 */
int poll(struct queue *q) {
  if (is_empty(q)) {
    printf("error: q is empty.");
    exit(1);
  }
  int v = q->array[q->first];
  q->first = (q->first + 1) % Q_SIZE;
  return v;
}

/**
 * 深さ優先探索
 */
void dfs(int v) {
  if (v < 0 || N <= v) return;

  printf("visit: %d\n", v);
  visited[v] = 1;

  for (int i = 0; i < N; i++) {
    if (G[v][i] && !visited[i]) dfs(i);
  }
}

/**
 * 幅優先探索
 */
void bfs(int v) {
  if (v < 0 || N <= v) return;

  struct queue *q = new_queue();

  visited[v] = 1;
  offer(v, q);

  while (!is_empty(q)) {
    v = poll(q);
    printf("visit: %d\n", v);

    for (int i = 0; i < N; i++) {
      if (G[v][i] && !visited[i]) {
        visited[i] = 1;
        offer(i, q);
      }
    }
  }
}

int main() {

  for (int i = 0; i < 8; i++) visited[i] = 0;

  // 深さ優先探索
  printf("Depth First Search\n");
  dfs(0);

  for (int i = 0; i < 8; i++) visited[i] = 0;
  printf("\n");

  // 幅優先探索
  printf("Breadth First Search\n");
  bfs(0);

  return 0;
}
