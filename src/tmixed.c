#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/workloads.h"
#include "../include/mixed.h"
#include "../include/mypapi.h"
#include "../include/libmapping.h"

uint32_t papi_enabled = 0;
uint32_t os_enabled = 0;
extern thread_data_t *threads;
extern uint32_t nt;

int compare(const void *s1, const void *s2){
	thread_data_t *t1 = (thread_data_t *) s1;
	thread_data_t *t2 = (thread_data_t *) s2;
	int cmp = strcmp(workload_name[t1->typeA], workload_name[t2->typeA]);

	if(cmp > 0 || (cmp == 0 && t1->memoryA > t2->memoryA) || (cmp == 0 && t1->memoryA == t2->memoryA && t1->time > t2->time))
		return 1;
	return -1;
}

int main(int argc, char **argv){
	printf("PAPI-based microarchitectural benchmark\n\n");
	uint64_t i, j, memory;
	double min, max, avg;
	workload_t workload;
	pthread_t *ts = NULL;

	if(argc != 4){
		fprintf(stderr, "Usage: %s <workloads-comma-separed> <heterogeneous | homogeneos | random> <class>\n", argv[0]);
		fprintf(stderr, "Workloads list:\n\t");
		for(i = 0; i < NWORKLOADS; i++){
			fprintf(stderr, "%s ", workload_name[i]);
			if(i == 4 || i == 10 || i == 16 || i == 21)
				fprintf(stderr, "\n\t");
		}
		fprintf(stderr, "\nClass list:\n");
		fprintf(stderr, "\tA -  5 seconds\n");
		fprintf(stderr, "\tB - 30 seconds\n");
		fprintf(stderr, "\tC - 60 seconds\n");
		exit(EXIT_FAILURE);
	}
	ts = malloc(nt * sizeof(pthread_t));
	assert(ts != NULL);

	map_env(argv[2]);
	parse_type_vector(argv[1], argv[3][0]);

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
	printf("\n\n");

	if(papi_enabled)
		papi_init();

	for(i = 0; i < nt; i++)
		pthread_create(&ts[i], NULL, pthreads_callback, &threads[i]);

	for(i = 0; i < nt; i++)
		pthread_join(ts[i], NULL);

	for(i = 0; i < nt; i++){
		if(threads[i].typeA == MEMORY_LOAD_DEP)
			free_list(&threads[i]);
		else if(threads[i].typeA == MEMORY_LOAD_IND || threads[i].typeA == MEMORY_LOAD_RANDOM || threads[i].typeA == MEMORY_STORE_IND || threads[i].typeA == MEMORY_STORE_RANDOM)
			free_vec(&threads[i]);
		
	}
/*
	qsort(threads, nt, sizeof(thread_data_t), compare);
*/
	workload = threads[0].typeA;
	memory = threads[0].memoryA;
	j = 1;
	min = threads[0].time;
	max = threads[0].time;
	avg = threads[0].time;
	for(i = 1; i < nt; i++){
		if(threads[i].typeA == workload && threads[i].memoryA == memory){
			avg += threads[i].time;
			max = threads[i].time;
			j++;
		}else{
			if(memory == 0){
				fprintf(stderr, "%s:min:%lf\n", workload_name[workload], min);
				fprintf(stderr, "%s:max:%lf\n", workload_name[workload], max);
				fprintf(stderr, "%s:avg:%lf\n", workload_name[workload], avg / (double) j);
			}else{
				fprintf(stderr, "%s-%luKB:min:%lf\n", workload_name[workload], memory, min);
				fprintf(stderr, "%s-%luKB:max:%lf\n", workload_name[workload], memory, max);
				fprintf(stderr, "%s-%luKB:avg:%lf\n", workload_name[workload], memory, avg / (double) j);
			}
			workload = threads[i].typeA;
			memory = threads[i].memoryA;
			j = 1;
			min = threads[i].time;
			max = threads[i].time;
			avg = threads[i].time;
		}
	}
	if(memory == 0){
		fprintf(stderr, "%s:min:%lf\n", workload_name[workload], min);
		fprintf(stderr, "%s:max:%lf\n", workload_name[workload], max);
		fprintf(stderr, "%s:avg:%lf\n", workload_name[workload], avg / (double) j);
	}else{
		fprintf(stderr, "%s-%luKB:min:%lf\n", workload_name[workload], memory, min);
		fprintf(stderr, "%s-%luKB:max:%lf\n", workload_name[workload], memory, max);
		fprintf(stderr, "%s-%luKB:avg:%lf\n", workload_name[workload], memory, avg / (double) j);
	}

	map_terminate();

	// free(ts);

	return 0;
}
