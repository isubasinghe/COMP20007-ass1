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
		//This is just to stop -pedantic from
		// complaining.
		list = list+1;
		list = list-1;
	}

	// Use a priority queue based top k 
	// to find the highest n_results.
	free(scores);
}

// see Assignment spec: 'Task 2: Priority queue-based multi-way merge approach'
void print_merge_results(Index *index, int n_results) {

	printf("not yet implemented: put code for task 2 here\n");

}
