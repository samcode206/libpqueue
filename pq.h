#ifndef LIBPQH
#define LIBPQH
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PQ_SIZE 511 // todo: make this dynamic 
#define PQ_PARENT(x) x == 1 ? -1 : (x >> 1)
#define PQ_LEFT(x) x << 1

#define PQ_INIT(type)                                                          \
  typedef struct type##PriorityQueue {                                         \
    type elems[PQ_SIZE];                                                       \
    size_t n;                                                                  \
  } type##PriorityQueue;                                                       \
                                                                               \
  static inline bool type##PriorityQueueCompare(type *a, type *b);             \
                                                                               \
  type##PriorityQueue *type##PriorityQueueCreate() {                           \
    type##PriorityQueue *pq =                                                  \
        (type##PriorityQueue *)malloc(sizeof(type##PriorityQueue));            \
    if (!pq)                                                                   \
      return pq;                                                               \
    pq->n = 0;                                                                 \
    memset(pq->elems, 0, sizeof(*pq->elems));                                  \
    return pq;                                                                 \
  }                                                                            \
                                                                               \
  void type##PriorityQueueDestroy(type##PriorityQueue *pq) {                   \
    pq->n = 0;                                                                 \
    free(pq);                                                                  \
  }                                                                            \
                                                                               \
  static void type##PriorityQueueSwap__(type##PriorityQueue *pq, size_t a,     \
                                        size_t b) {                            \
    type tmp = pq->elems[a];                                                   \
    pq->elems[a] = pq->elems[b];                                               \
    pq->elems[b] = tmp;                                                        \
  }                                                                            \
                                                                               \
  void type##PriorityQueueBubbleUp__(type##PriorityQueue *pq, size_t pos) {    \
    size_t parent = PQ_PARENT(pos);                                            \
    if (parent == -1) {                                                        \
      return;                                                                  \
    }                                                                          \
    /* Todo: generic compare  */                                               \
    if (type##PriorityQueueCompare(&pq->elems[parent], &pq->elems[pos])) {     \
      type##PriorityQueueSwap__(pq, pos, parent);                              \
      type##PriorityQueueBubbleUp__(pq, parent);                               \
    }                                                                          \
  }                                                                            \
                                                                               \
  void type##PriorityQueueBubbleDown__(type##PriorityQueue *pq, size_t pos) {  \
    size_t child, i, minIdx;                                                   \
    child = PQ_LEFT(pos);                                                      \
    minIdx = pos;                                                              \
                                                                               \
    for (i = 0; i < 2; i++) {                                                  \
      if ((child + i) <= pq->n) {                                              \
        /* Todo: generic compare  */                                           \
        if (type##PriorityQueueCompare(&pq->elems[minIdx],                     \
                                       &pq->elems[child + i])) {               \
          minIdx = child + i;                                                  \
        }                                                                      \
      }                                                                        \
    }                                                                          \
                                                                               \
    if (minIdx != pos) {                                                       \
      type##PriorityQueueSwap__(pq, pos, minIdx);                              \
      type##PriorityQueueBubbleDown__(pq, minIdx);                             \
    }                                                                          \
  }                                                                            \
  size_t type##PriorityQueueSize(type##PriorityQueue *pq) { return pq->n; }    \
                                                                               \
  int type##PriorityQueueInsert(type##PriorityQueue *pq, type elem) {          \
    if (pq->n >= PQ_SIZE)                                                      \
      return -1;                                                               \
    pq->n++;                                                                   \
    size_t i = pq->n;                                                          \
    pq->elems[i] = elem;                                                       \
    type##PriorityQueueBubbleUp__(pq, i);                                      \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  type type##PriorityQueuePop(type##PriorityQueue *pq) {                       \
    if (!pq->n)                                                                \
      return pq->elems[0];                                                     \
    type top = pq->elems[1];                                                   \
    pq->elems[1] = pq->elems[pq->n];                                           \
    pq->n--;                                                                   \
    type##PriorityQueueBubbleDown__(pq, 1);                                    \
    return top;                                                                \
  }                                                                            \
                                                                               \
  type type##PriorityQueueTop(type##PriorityQueue *pq) {                       \
    return pq->elems[pq->n ? 1 : 0];                                           \
  }                                                                            \
  type##PriorityQueue *type##PriorityQueueFrom(type *arr, size_t count) {      \
    type##PriorityQueue *pq = type##PriorityQueueCreate();                     \
    if (!pq)                                                                   \
      return pq;                                                               \
    /*count is truncated if more than PQ_SIZE*/                                \
    count = count % PQ_SIZE;                                                   \
    size_t i = 0;                                                              \
    pq->n = count;                                                             \
    for (; i < count; i++)                                                     \
      pq->elems[i + 1] = arr[i];                                               \
    for (i = pq->n / 2; i >= 1; i--)                                           \
      type##PriorityQueueBubbleDown__(pq, i);                                  \
    return pq;                                                                 \
  }

#endif /* LIBPQH */
