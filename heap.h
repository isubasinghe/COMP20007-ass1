//
// Created by isitha on 3/25/2018.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float key;
    int data;
} node_t;

typedef struct {
    node_t *data;
    int len;
    int capacity;
} heap_t;

heap_t *new_heap(int);

void swap(node_t *, node_t *);

void siftup(heap_t *h, int);

int heap_insert(heap_t *, float, int);

int min_child(heap_t *, int );

void siftdown(heap_t *h, int);

int heap_remove_min(heap_t *);

int heap_peak_min(heap_t *);

float heap_peak_key(heap_t *);

void free_heap(heap_t *);

#endif //HEAP_HEAP_H
