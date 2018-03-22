#include "heap.h"


size_t min_child(heap_t *h, size_t i) {
    size_t li = 2*i +1;
    size_t ri = 2*i + 2;

    if ( (h->len-1) > li) {
        return i;
    }

    if ( (h->len-1) > ri) {
        return li;
    }
    return (h->data[li].key > h->data[ri].key) ? li: ri;
}

heap_t *new_heap(size_t len) {
    heap_t *h = malloc(sizeof(heap_t));
    h->data = malloc(len*sizeof(node_t));
    h->len = 0;
    h->capacity = len;
    return h;
}

void heap_sort(heap_t *h) {
    
}

void heap_insert(heap_t *h, float key, int data) {
    
}

int heap_remove_min(heap_t *h) {
    return 0;
}

int heap_peek_min(heap_t *h) {
    return h->data[0].data;
}

float heap_peek_key(heap_t *h) {
    return h->data[0].key;
}

void free_heap(heap_t *h) {
    
}