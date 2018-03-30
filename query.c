/* ... */

#define TEST_SUITE_ON


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "query.h"
#include "list.h"
#include "heap.h"

// Test suite for timing the functions in task 1 and 2.
#ifdef TEST_SUITE_ON
#include <time.h>

void write_csv(int task, int n_results, int num_terms, 
				int n_documents, float time, long int cpu_ticks) {

	FILE *fp = fopen("./data.csv", "a");
	if (fp == NULL) {return;}

	fprintf(fp, "%d, %d, %d, %d, %f, %ld\n", 
		task, n_results, num_terms, n_documents, time, cpu_ticks);

	fclose(fp);
}

#endif //TEST_SUITE_ON


// see Assignment spec: 'Task 1: Array-based accumulation approach'
void print_array_results(Index *index, int n_results, int n_documents) {
	
	#ifdef TEST_SUITE_ON
	clock_t start_t, end_t;
	float total=0.0;
	printf("Starting test\n");
	start_t = clock();
	
	#endif // TEST_SUITE_ON

	// Allocate n_documents scores
	float *scores = malloc(n_documents*sizeof(float));
	assert(scores != NULL);

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
	assert(h != NULL);

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
	assert(ids != NULL);

	for(int i=0; i < n_results; i++) {
		float score = heap_peak_key(h);
		int id = heap_remove_min(h);
		// Re-use the score array to save space.
		scores[n_results-1-i] = score;
		ids[i] = id;
	}
	free_heap(h);

	for(int i=0; i < n_results; i++) {
		#ifndef TEST_SUITE_ON
		//printf("%6d %.6f\n", ids[i], scores[i]);
		printf("%6d %.6f\n", ids[i], scores[i]);
		#endif // TEST_SUITE_ON
	}

	free(ids);
	free(scores);


	
	#ifdef TEST_SUITE_ON
	end_t = clock();
	total = (float)((end_t - start_t)/CLOCKS_PER_SEC);
	write_csv(1, n_results, index->num_terms, 
		n_documents, total, (long int)(end_t - start_t));
	printf("%f\n", total);
	printf("%ld", (long int)(end_t - start_t));
	#endif // TEST_SUITE_ON
}



// see Assignment spec: 'Task 2: Priority queue-based multi-way merge approach'
void print_merge_results(Index *index, int n_results) {

	#ifdef TEST_SUITE_ON
	clock_t start_t, end_t;
	float total=0.0;
	printf("Starting test\n");
	start_t = clock();
	#endif // TEST_SUITE_ON
	
	heap_t *topk = new_heap(n_results);
	assert(topk!=NULL);

	Node **nodes = malloc(index->num_terms *sizeof(Node *));
	assert(nodes!=NULL);

	for(int i=0; i<index->num_terms; i++) {
		nodes[i] = index->doclists[i]->head;
	}

	while(TRUE) {

		heap_t *index_heap = new_heap(index->num_terms);
		assert(index_heap!=NULL);

		int null_c = 0;
		for(int i=0; i < index->num_terms; i++) {
			if(nodes[i] == NULL) {
				null_c++;
				continue;
			}else {
				Document *doc = (Document *)nodes[i]->data;
				heap_insert(index_heap, doc->id, i);
			}
			
		}

		if(null_c >= index->num_terms) break;

		int id = heap_peak_key(index_heap);
		float score = 0.0;
		while(index_heap->len > 0) {
			int temp_id = heap_peak_key(index_heap);
			if(temp_id == id) {
				int i = heap_remove_min(index_heap);
				Document *doc = (Document *)nodes[i]->data;
				score += doc->score;
				nodes[i] = nodes[i]->next;
			}else {
				break;
			}
		}

		if(topk->len < n_results) {
			heap_insert(topk, score, id);
		}else {
			float min = heap_peak_key(topk);
			if(min < score) {
				heap_remove_min(topk);
				heap_insert(topk, score, id);
			}
		}

		free_heap(index_heap);
	}
	float *scores = malloc(n_results*sizeof(float));
	assert(scores!=NULL);
	int *ids = malloc(n_results*sizeof(int));
	assert(ids!=NULL);

	for(int i=0; i < n_results; i++) {
		scores[n_results-1-i] = heap_peak_key(topk);
		ids[n_results-1-i] = heap_remove_min(topk);
	}

	for(int i=0; i<n_results; i++) {
		#ifndef TEST_SUITE_ON
		printf("%6d %0.6f\n", ids[i], scores[i]);
		#endif //TEST_SUITE_ON
	}

	free_heap(topk);

	#ifdef TEST_SUITE_ON
	end_t = clock();
	total = (float)((end_t - start_t)/CLOCKS_PER_SEC);
	write_csv(2, n_results, index->num_terms, 
		-1, total, (long int)(end_t - start_t));
	printf("%f\n", total);
	printf("%ld", (long int)(end_t - start_t));
	#endif // TEST_SUITE_ON

}
