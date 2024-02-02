#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PQ_SIZE 511


typedef struct {
  int elems[PQ_SIZE + 1];
  size_t n;
} PriorityQueue;

static void pq_swap(PriorityQueue *pq, size_t a, size_t b);
static void pq_bubble_up(PriorityQueue *pq, size_t pos);
static void pq_bubble_down(PriorityQueue *pq, size_t pos);

PriorityQueue *pq_create(void);
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
