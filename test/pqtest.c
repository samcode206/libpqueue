#include "../pq.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  int x;
} Order;

static inline bool OrderPriorityQueueCompare(Order *a, Order *b) {
  return (a->x) > (b->x); // min heap
}

PQ_INIT(Order);

typedef int Number;

PQ_INIT(Number);

static inline bool NumberPriorityQueueCompare(Number *a, Number *b) {
  return *a < *b; // max heap
}

int main(void) {
  Order nums[] = {{3}, {4}, {5}, {7}, {8}, {9}, {10}, {1}, {2}, {6}};
  OrderPriorityQueue *pq = OrderPriorityQueueFrom(nums, 10);
  printf("Order Queue (Min Heap): ");
  while (OrderPriorityQueueSize(pq)) {
    printf("%d ", OrderPriorityQueuePop(pq).x);
  }
  printf("\n");
  OrderPriorityQueueDestroy(pq);
  pq = NULL;

  NumberPriorityQueue *nq = NumberPriorityQueueCreate();
  for (int i = i; i <= 10; i++)
    NumberPriorityQueueInsert(nq, i);
  printf("Number Queue (Max Heap): ");
  while (NumberPriorityQueueSize(nq)) {
    printf("%d ", NumberPriorityQueuePop(nq));
  }
  printf("\n");
}
