#include "pq.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int x;
} Order;

// typedef int Order;

PQ_INIT(Order);

static inline bool OrderPriorityQueueCompare(Order *a, Order *b) {
  return (a->x) > (b->x);
}

int main(void) {
  Order nums[] = {{5}, {4}, {3}, {2}, {1}, {9}, {7}, {8}};
  OrderPriorityQueue *pq = OrderPriorityQueueFrom(nums, 8);
  while (OrderPriorityQueueSize(pq)) {
    printf("%d\n", OrderPriorityQueuePop(pq).x);
  }
}
