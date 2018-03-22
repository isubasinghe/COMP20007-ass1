#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    float key;
} node_t;

typedef struct {
    node_t *data;
    size_t len;
    size_t capacity;
} heap_t;

void siftup(heap_t *h, size_t i);

void siftdown(heap_t *h, size_t i);

size_t min_child(heap_t *h, size_t i);

heap_t *new_heap(size_t len);

void heap_insert(heap_t *h, float key, int data);

int heap_remove_min(heap_t *h);

int heap_peek_min(heap_t *h);

float heap_peek_key(heap_t *h);

void free_heap(heap_t *h);
