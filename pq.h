#ifndef LIBPQH
#define LIBPQH
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PQ_SIZE 4095 // todo: make this dynamic
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

/**
before macro insanity above we had this
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PQ_SIZE 511


typedef struct {
  int elems[PQ_SIZE + 1];
  size_t n;
} PriorityQueue;

static void pq_swap(PriorityQueue *pq, size_t a, size_t b);
static void pq_bubble_up(PriorityQueue *pq, size_t pos);
static void pq_bubble_down(PriorityQueue *pq, size_t pos);

PriorityQueue *pq_create(void);
PriorityQueue *pq_from_array(int *nums, size_t count);
int pq_insert(PriorityQueue *pq, int elem);
int pq_top(PriorityQueue *pq);
int pq_pop(PriorityQueue *pq);
size_t pq_size(PriorityQueue *pq);
void pq_destroy(PriorityQueue *pq);

PriorityQueue *pq_create(void) {
  PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
  if (!pq)
    return pq;
  pq->n = 0;
  memset(pq->elems, 0, sizeof(int));
  return pq;
}

PriorityQueue *pq_from_array(int *nums, size_t count){
    PriorityQueue *pq = pq_create();
    if (!pq) return pq;
    if (PQ_SIZE < count) {
        pq_destroy(pq);
        return NULL;
    };

    size_t i = 0;
    pq->n = count;
    for (; i < count; i++) pq->elems[i+1] = nums[i];
    for (i = pq->n/2; i >= 1; i--) pq_bubble_down(pq, i);
    return pq;
};

int pq_insert(PriorityQueue *pq, int elem) {
  if (pq->n >= PQ_SIZE)
    return -1;
  pq->n++;
  register size_t i = pq->n;
  pq->elems[i] = elem;
  pq_bubble_up(pq, i);
  return 0;
}

int pq_top(PriorityQueue *pq) {
  // returns zero value element at position 0 when empty
  // caller should check size before calling pq_top to avoid
  // confusion
  return pq->elems[pq->n ? 1 : 0];
}

int pq_pop(PriorityQueue *pq) {
  if (!pq->n)
    return pq->elems[0];
  int top = pq->elems[1];
  pq->elems[1] = pq->elems[pq->n];
  pq->n--;
  pq_bubble_down(pq, 1);
  return top;
}

size_t pq_size(PriorityQueue *pq) { return pq->n; }

void pq_destroy(PriorityQueue *pq) {
  pq->n = 0;
  free(pq);
}

#define PQ_PARENT(x) x == 1 ? -1 : (x / 2)
#define PQ_LEFT(x) 2 * x


static void pq_swap(PriorityQueue *pq, size_t a, size_t b) {
  int tmp = pq->elems[a];
  pq->elems[a] = pq->elems[b];
  pq->elems[b] = tmp;
}

static void pq_bubble_up(PriorityQueue *pq, size_t pos) {
  size_t parent = PQ_PARENT(pos);
  if (parent == -1) {
    return;
  }

  if (pq->elems[parent] > pq->elems[pos]) {
    pq_swap(pq, pos, parent);
    pq_bubble_up(pq, parent);
  }
}

static void pq_bubble_down(PriorityQueue *pq, size_t pos) {
  size_t child, i, minIdx;
  child = PQ_LEFT(pos);
  minIdx = pos;

  for (i = 0; i < 2; i++) {
    if ((child + i) <= pq->n) {
      if (pq->elems[minIdx] > pq->elems[child + i]) {
        minIdx = child + i;
      }
    }
  }

  if (minIdx != pos) {
    pq_swap(pq, pos, minIdx);
    pq_bubble_down(pq, minIdx);
  }
}

int main(void) {
//   PriorityQueue *pq = pq_create();

//  int count = 10;

//  while (count){
//     pq_insert(pq, count);
//     assert(pq_top(pq) == count);
//     count--;
//  }

  int nums[] = {5,4,3,2,1,9,7,8};
   PriorityQueue *pq = pq_from_array(nums, 8);
  while (pq_size(pq)){
    printf("%d\n", pq_pop(pq));
  }
}



*/