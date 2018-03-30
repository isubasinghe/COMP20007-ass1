//
// Created by isitha on 3/25/2018.
//
#include "heap.h"

heap_t *new_heap(int len) {
    heap_t *h = malloc(sizeof(heap_t));
    h->data = malloc(sizeof(node_t)*len);
    h->capacity = len;
    h->len = 0;
    return h;
}

void swap(node_t *a, node_t *b) {
    node_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void siftup(heap_t *h, int child) {
    while(1) {
        int parent = (child-1)/2;
        if(child==0) {
            return;
        }
        if(h->data[parent].key > h->data[child].key) {
            swap(&h->data[parent], &h->data[child]);
            child = parent;
        }else {
            return;
        }
    }

}

int heap_insert(heap_t *h, float key, int data) {
    if(h->capacity <= h->len) {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity*sizeof(node_t));
        if(h->data == NULL) {
            perror("HEAP MODULE: HEAP_INSERT: Out of Memory\n\n");
            h->capacity = 0;
            h->len = 0;
            return FALSE;
        }
    }

    h->data[h->len].key = key;
    h->data[h->len].data = data;
    h->len++;
    siftup(h, h->len-1);
    return TRUE;
}

int min_child(heap_t *h, int parent) {
    int li = 2*parent+1;
    int ri = 2*parent+2;

    if(li > h->len-1) {
        return parent;
    }
    if(ri > h->len-1) {
        return li;
    }

    return (h->data[li].key > h->data[ri].key) ? ri:li;
}

void siftdown(heap_t *h, int parent) {
    while(1) {
        int child = min_child(h, parent);

        if(child == parent) {
            return;
        }

        if(h->data[child].key < h->data[parent].key) {
            swap(&h->data[child], &h->data[parent]);
            parent = child;
        }else {
            return;
        }

    }
}

int heap_remove_min(heap_t *h) {
    if(h->len<=0) {
        return -1;
    }

    int min_val = h->data[0].data;

    swap(&h->data[0], &h->data[h->len-1]);
    h->len--;
    siftdown(h, 0);

    return min_val;
}

int heap_peak_min(heap_t *h) {
    if(h->len <= 0) {
        return -1;
    }

    return h->data[0].data;
}

float heap_peak_key(heap_t *h) {
    if(h->len <= 0) {
        return NAN;
    }
    return h->data[0].key;
}

void free_heap(heap_t *h) {
    free(h->data);
    free(h);
}