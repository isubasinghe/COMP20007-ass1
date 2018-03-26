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
	} // O(d)


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
	} // O(dt)

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

	int *ids = malloc(n_results*sizeof(int));

	for(int i=0; i < n_results; i++) {
		float score = heap_peak_key(h);
		int id = heap_remove_min(h);
		// Re-use the score array to save space.
		scores[n_results-1-i] = score;
		ids[i] = id;
	}
	free_heap(h);

	for(int i=0; i < n_results; i++) {
		printf("%6d %.6f\n", ids[i], scores[i]);
	}

	free(ids);
	free(scores);
}

// see Assignment spec: 'Task 2: Priority queue-based multi-way merge approach'
void print_merge_results(Index *index, int n_results) {

	printf("not yet implemented: put code for task 2 here\n");

}
