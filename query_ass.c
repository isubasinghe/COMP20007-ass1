// Done by Isitha Subasinghe 911584
// University of Melbourne
// Semester 1 - 2018
// COMP20007 - Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "query.h"
#include "list.h"
#include "heap.h"

void check_insert(heap_t *h, float score, int id, float n_results) {
	if(h->len < n_results) { 
		heap_insert(h, score, id);
	}else {
		float min_val = heap_peak_key(h);
		if(score > min_val) {
			heap_remove_min(h);
			heap_insert(h, score, id);
		}
	}
}

void print_score_id(float *scores, int *ids, size_t len) {
	for(int i=0; i < len; i++) {
		if(ids[i]==-1) continue;
		if(scores[i]==0.0) continue;
		printf("%6d %.6f\n", ids[i], scores[i]);
	}
		
}

// see Assignment spec: 'Task 1: Array-based accumulation approach'
void print_array_results(Index *index, int n_results, int n_documents) {
	// Allocate n_documents scores
	float *scores = malloc(n_documents*sizeof(float));
	assert(scores != NULL);

	for(int i=0; i < n_documents; i++) {
		// We need to assure that all the elems are 0.
		scores[i] = 0.0;
	} 

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
	} 
	
	heap_t *topk = new_heap(n_results);
	assert(topk!=NULL);

	for(int i=0; i < n_documents; i++) {
		check_insert(topk, scores[i], i, n_results);
	}

	//Store the ids in this.
	int *ids = malloc(n_results*sizeof(int));
	assert(ids!=NULL);


	for(int i=0; i < n_results; i++) {
		//Save a little bit of memory and cut overhead,
		// by using the scores array.
		scores[n_results-1-i] = heap_peak_key(topk);
		ids[n_results-1-i] = heap_remove_min(topk);
	}

	print_score_id(scores, ids, n_results);

	free_heap(topk);
}

// see Assignment spec: 'Task 2: Priority queue-based multi-way merge approach'
void print_merge_results(Index *index, int n_results) {
	// Store the top n results in a heap.
	heap_t *topk = new_heap(n_results);
	assert(topk!=NULL);

	Node **nodes = malloc(index->num_terms *sizeof(Node *));
	assert(nodes!=NULL);

	// Intialise the nodes array.
	for(int i=0; i<index->num_terms; i++) {
		nodes[i] = index->doclists[i]->head;
	}

	while(TRUE) {

		heap_t *index_heap = new_heap(index->num_terms);
		assert(index_heap!=NULL);

		//Count the number of null nodes.
		int null_c = 0;
		for(int i=0; i < index->num_terms; i++) {
			if(nodes[i] == NULL) {
				null_c++;
				continue; // We cant process null nodes.
			}else {
				Document *doc = (Document *)nodes[i]->data;
				heap_insert(index_heap, doc->id, i);
			}
		}
		// If the number of null nodes >= number of terms, 
		// we have gone through all the doclists till they are empty.
		// This is our exit case.
		if(null_c >= index->num_terms) break;

		int id = heap_peak_key(index_heap);
		float score = 0.0; // Initialise a score to zero.
		while(index_heap->len > 0) {
			int temp_id = heap_peak_key(index_heap);
			// Check to see if we are operating on the same doc id.
			if(temp_id == id) {
				int i = heap_remove_min(index_heap);
				Document *doc = (Document *)nodes[i]->data;
				score += doc->score;
				// this node has been dealt with, move on to the next.
				nodes[i] = nodes[i]->next;
			}else {
				break;
			}
		}
		// Insert to our heap if the heap is empty.
		check_insert(topk, score, id, n_results);

		free_heap(index_heap);
	}
	// Store our scores and ids in an array.
	float *scores = malloc(n_results*sizeof(float));
	assert(scores!=NULL);
	int *ids = malloc(n_results*sizeof(int));
	assert(ids!=NULL);

	//Insert in reverse order to the scores and ids array.
	for(int i=0; i < n_results; i++) {
		scores[n_results-1-i] = heap_peak_key(topk);
		ids[n_results-1-i] = heap_remove_min(topk);
	}

	print_score_id(scores, ids, n_results);
	free_heap(topk);
}
