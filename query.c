/* ... */

#include <stdio.h>
#include <stdlib.h>

#include "query.h"
#include "list.h"
#include "heap.h"

// see Assignment spec: 'Task 1: Array-based accumulation approach'
void print_array_results(Index *index, int n_results, int n_documents) {
	
	// Allocate n_documents scores
	float *scores = malloc(n_documents*sizeof(float));

	for(int i=0; i < n_documents; i++) {
		// We need to assure that all the elems are 0.
		scores[i] = 0.0;
	} // O(d)


	for(int i=0; i < index->num_terms; i++) {
		// For each document in this list
		// obtain the id and score
		// then do a scores[id] += score;
		List *list = index->doclists[i];

		//Obtain the first node of the list.
		Node *node = list->head;
		
		//While the node is valid.
		while(node != NULL) {
			Document *doc = (Document *)node->data;
			scores[doc->id] += doc->score;
			// Move onto the next node.
			node = node->next;
		}
	} // O(dt)

	// Store the top k in a priority queue.
	heap_t *h = new_heap(n_results);

	for(int i=0; i < n_documents; i++) {
		// We haven't filled the heap yet.
		if(i < n_results) {
			heap_insert(h, scores[i], i); 
		// Heap is full
		}else {
			//Extract the minimum key val
			float min_val = heap_peak_key(h);
			// If the current value is bigger than
			// the smallest value in our min heap.
			if(scores[i] > min_val) {
				// The smallest in the heap
				// is no longer among the top k.
				heap_remove_min(h);
				// The new value belongs in the top k.
				heap_insert(h, scores[i], i);  
			}
		}
	} 

	//Need to store the ids.
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

	

}
