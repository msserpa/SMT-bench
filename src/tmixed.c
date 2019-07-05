#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/workloads.h"
#include "../include/mixed.h"
#include "../include/mypapi.h"
#include "../include/libmapping.h"

uint32_t papi_enabled = 0;
extern thread_data_t *threads;
extern uint32_t nt;

int compare(const void *s1, const void *s2){
	thread_data_t *t1 = (thread_data_t *) s1;
	thread_data_t *t2 = (thread_data_t *) s2;
	int cmp = strcmp(workload_name[t1->typeA], workload_name[t2->typeA]);

	if(cmp > 0 || (cmp == 0 && t1->memoryA > t2->memoryA))
		return 1;
	return -1;
}

int main(int argc, char **argv){
	printf("PAPI-based microarchitectural benchmark\n\n");
	uint64_t i, loops, memory;
	workload_t workload;
	pthread_t *ts = NULL;

	if(argc != 4){
		fprintf(stderr, "Usage: %s <workloads-comma-separed> <heterogeneous | homogeneos | random> <time>\n", argv[0]);
		fprintf(stderr, "Workloads list:\n");
		for(i = 0; i < NWORKLOADS; i++)
			fprintf(stderr, "\t%s\n", workload_name[i]);
		exit(EXIT_FAILURE);
	}
	ts = malloc((nt + 1) * sizeof(pthread_t));
	assert(ts != NULL);

	map_env(argv[2]);
	parse_type_vector(argv[1]);

	if(getenv("OMP_NUM_THREADS"))
		nt = atoi(getenv("OMP_NUM_THREADS"));
	else {
		printf("missing OMP_NUM_THREADS\n");
		exit(1);
	}

	if(getenv("PAPI_EVENT") == NULL){
		papi_enabled = 0;
		printf("PAPI: disabled\n\n");
	}else{
		papi_enabled = 1;
		printf("PAPI: enabled\n\n");
	}

	init_workload();
	for(i = 0; i < nt; i++){
		if(threads[i].typeA == MEMORY_LOAD_DEP)
			alloc_list(&threads[i]);
		else if(threads[i].typeA == MEMORY_LOAD_IND || threads[i].typeA == MEMORY_LOAD_RANDOM || threads[i].typeA == MEMORY_STORE_IND || threads[i].typeA == MEMORY_STORE_RANDOM){
			alloc_vec(&threads[i]);
			if(threads[i].typeA == MEMORY_LOAD_RANDOM)
				init_vec(&threads[i]);
		}
		if(threads[i].memoryA == 0)	
			printf("%s(%d)", workload_name[threads[i].typeA], threads[i].cpu);
		else
			printf("%s-%luKB(%d)", workload_name[threads[i].typeA], threads[i].memoryA, threads[i].cpu);
		if(i < nt - 1)
			printf(", ");
	}
	printf("\n");

	if(papi_enabled)
		papi_init();

	for(i = 0; i < nt; i++)
		pthread_create(&ts[i], NULL, pthreads_callback, &threads[i]);

	pthread_create(&ts[nt], NULL, time_monitor, (void *) atol(argv[3]));

	for(i = 0; i < nt; i++)
		pthread_join(ts[i], NULL);

	pthread_join(ts[nt], NULL);

	for(i = 0; i < nt; i++){
		if(threads[i].typeA == MEMORY_LOAD_DEP)
			free_list(&threads[i]);
		else if(threads[i].typeA == MEMORY_LOAD_IND || threads[i].typeA == MEMORY_LOAD_RANDOM || threads[i].typeA == MEMORY_STORE_IND || threads[i].typeA == MEMORY_STORE_RANDOM)
			free_vec(&threads[i]);
		
	}

	qsort(threads, nt, sizeof(thread_data_t), compare);


	for(i = 0; i < nt; i++){
		if(threads[i].memoryA == 0)
			fprintf(stderr, "%s:%lu\n", workload_name[threads[i].typeA], threads[i].loops);
		else
			fprintf(stderr, "%s-%luKB:%lu\n", workload_name[threads[i].typeA], threads[i].memoryA, threads[i].loops);		
	}

	// workload = threads[0].typeA;
	// memory = threads[0].memoryA;
	// loops = threads[0].loops;
	// for(i = 1; i < nt; i++){
	// 	if(threads[i].typeA == workload && threads[i].memoryA == memory)
	// 		loops += threads[i].loops;
	// 	else{
	// 		if(memory == 0)
	// 			fprintf(stderr, "%s:%lu\n", workload_name[workload], loops);
	// 		else
	// 			fprintf(stderr, "%s-%luKB:%lu\n", workload_name[workload], memory, loops);
	// 		workload = threads[i].typeA;
	// 		memory = threads[i].memoryA;
	// 		loops = threads[i].loops;
	// 	}
	// }
	// if(memory == 0)
	// 	fprintf(stderr, "%s:%lu\n", workload_name[workload], loops);
	// else
	// 	fprintf(stderr, "%s-%luKB:%lu\n", workload_name[workload], memory, loops);

	// for(i = 0; i < NWORKLOADS; i++)
	// 	loops[i] = 0;

	// for(i = 0; i < nt; i++)
	// 	loops[threads[i].typeA] += threads[i].loops;

	// for(i = 0; i < NWORKLOADS; i++)
	// 	if(loops[i] != 0)
	// 		fprintf(stderr, "%s:%lu\n", workload_name[i], loops[i]);

	map_terminate();

	// free(ts);

	return 0;
}