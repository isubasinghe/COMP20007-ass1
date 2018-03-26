/* ... */

#include <stdio.h>
#include <stdlib.h>

#include "query.h"
#include "list.h"
#include "heap.h"

// see Assignment spec: 'Task 1: Array-based accumulation approach'
void print_array_results(Index *index, int n_results, int n_documents) {
	
	float *scores = malloc(n_documents*sizeof(float));

	for(int i=0; i < n_documents; i++) {
		scores[i] = 0.0;
	}


	for(int i=0; i < index->num_terms; i++) {
		// For each document in this list
		// obtain the id and score
		// then do a scores[id] += score;
		List *list = index->doclists[i];

		Node *node = list->head;

		while(node != NULL) {
			Document *doc = (Document *)node->data;
			scores[doc->id] += doc->score;
			node = node->next;
		}
	}

	heap_t *h = new_heap(n_results);

	for(int i=0; i < n_documents; i++) {
		if(i < n_results) {
			heap_insert(h, scores[i], i);
		}else {
			float min_val = heap_peak_key(h);
			if(scores[i] > min_val) {
				heap_remove_min(h);
				heap_insert(h, scores[i], i);
			}
		}
	}

	for(int i=0; i < n_results; i++) {
		float val = heap_peak_key(h);
		heap_remove_min(h);
		printf("%f\n", val);
	}

	free_heap(h);
	free(scores);
}

// see Assignment spec: 'Task 2: Priority queue-based multi-way merge approach'
void print_merge_results(Index *index, int n_results) {

	printf("not yet implemented: put code for task 2 here\n");

}
