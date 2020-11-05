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
extern uint32_t nt, nt_exec;

void swap(thread_data_t *A, thread_data_t *B){
    thread_data_t tmp = *A;
    *A = *B;
    *B = tmp;
}

void selection_sort(thread_data_t *A, int N){
    int i, j, min;
    for(i = 0; i < N - 1; i++){
        min = i;
        for(j = i + 1; j < N; j++){
            int cmp = strcmp(workload_name[A[j].typeA], workload_name[A[min].typeA]);
            if(cmp < 0 || (cmp == 0 && A[j].memoryA < A[min].memoryA) || (cmp == 0 && A[j].memoryA == A[min].memoryA && A[j].time < A[min].time))
                min = j;
        }
        if(A[i].tid != A[min].tid)
            swap(&A[i], &A[min]);
    }
}

int main(int argc, char **argv){
	printf("PAPI-based microarchitectural benchmark\n\n");
	uint64_t i, j = 0, memory;
	double min_time, max_time, avg_time;
	uint64_t min_iterations, max_iterations, avg_iterations;
	workload_t workload;
	pthread_t *ts = NULL;

	if(argc != 4){
		uint64_t line_breaks[] = {4, 10, 16, 19, 21, 22, 24, 28, 31, 33, 36, 39, 42, 45, 48, 51, 54, 63, 0};

		fprintf(stderr, "Usage: %s <workloads-comma-separed> <os | heterogeneous | homogeneos | random> <time_in_seconds>\n", argv[0]);
		fprintf(stderr, "Workloads list:\n\t");

		j = 0;
		for(i = 0; i < NWORKLOADS; i++){
			if(i >= 17 && i <= 21)
				fprintf(stderr, "%s:<size_in_KB> ", workload_name[i]);
			else
				fprintf(stderr, "%s ", workload_name[i]);

			if(i == line_breaks[j]){
				fprintf(stderr, "\n\t");
				j++;
			}
		}
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	ts = calloc(nt_exec + 1, sizeof(pthread_t));
	assert(ts != NULL);

	map_env(argv[2]);
	parse_type_vector(argv[1]);

	if(getenv("OMP_NUM_THREADS")){
		nt = atoi(getenv("OMP_NUM_THREADS"));
		printf("nt=%d nt_exec=%d time_in_seconds=%ld\n", nt, nt_exec, atol(argv[3]));
	}
	else{
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
	for(i = 0; i < nt_exec; i++){
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
		if(i < nt_exec - 1)
			printf(", ");
	}
	printf("\n\n");

	if(papi_enabled)
		papi_init();

	for(i = 0; i < nt_exec; i++)
		pthread_create(&ts[i], NULL, pthreads_callback, &threads[i]);

	pthread_create(&ts[nt_exec], NULL, time_monitor, (void *) atol(argv[3]));

	for(i = 0; i <= nt_exec; i++)
		pthread_join(ts[i], NULL);	
	
	for(i = 0; i < nt_exec; i++){
		if(threads[i].typeA == MEMORY_LOAD_DEP)
			free_list(&threads[i]);
		else if(threads[i].typeA == MEMORY_LOAD_IND || threads[i].typeA == MEMORY_LOAD_RANDOM || threads[i].typeA == MEMORY_STORE_IND || threads[i].typeA == MEMORY_STORE_RANDOM)
			free_vec(&threads[i]);
		
	}
	

	selection_sort(threads, nt_exec);

	workload = threads[0].typeA;
	memory = threads[0].memoryA;

	j = 1;

	min_time = threads[0].time;
	max_time = threads[0].time;
	avg_time = threads[0].time;

	min_iterations = threads[0].iterations;
	max_iterations = threads[0].iterations;
	avg_iterations = threads[0].iterations;

	for(i = 1; i < nt_exec; i++){
		if(threads[i].typeA == workload && threads[i].memoryA == memory){
			avg_time += threads[i].time;
			max_time = threads[i].time;

			avg_iterations += threads[i].iterations;
			max_iterations = threads[i].iterations;			

			j++;
		}else{
			if(memory == 0){
				fprintf(stderr, "%s : min : %lf : %lu\n", workload_name[workload], min_time, min_iterations);
				fprintf(stderr, "%s : max : %lf : %lu\n", workload_name[workload], max_time, max_iterations);
				fprintf(stderr, "%s : avg : %lf : %lu\n", workload_name[workload], avg_time / (double) j, avg_iterations / j);
			}else{
				fprintf(stderr, "%s-%luKB : min : %lf : %lu\n", workload_name[workload], memory, min_time, min_iterations);
				fprintf(stderr, "%s-%luKB : max : %lf : %lu\n", workload_name[workload], memory, max_time, max_iterations);
				fprintf(stderr, "%s-%luKB : avg : %lf : %lu\n", workload_name[workload], memory, avg_time / (double) j, avg_iterations / j);
			}
			workload = threads[i].typeA;
			memory = threads[i].memoryA;

			j = 1;

			min_time = threads[i].time;
			max_time = threads[i].time;
			avg_time = threads[i].time;

			min_iterations = threads[i].iterations;
			max_iterations = threads[i].iterations;
			avg_iterations = threads[i].iterations;			
		}
	}
	if(memory == 0){
		fprintf(stderr, "%s : min : %lf : %lu\n", workload_name[workload], min_time, min_iterations);
		fprintf(stderr, "%s : max : %lf : %lu\n", workload_name[workload], max_time, max_iterations);
		fprintf(stderr, "%s : avg : %lf : %lu\n", workload_name[workload], avg_time / (double) j, avg_iterations / j);
	}else{
		fprintf(stderr, "%s-%luKB : min : %lf : %lu\n", workload_name[workload], memory, min_time, min_iterations);
		fprintf(stderr, "%s-%luKB : max : %lf : %lu\n", workload_name[workload], memory, max_time, max_iterations);
		fprintf(stderr, "%s-%luKB : avg : %lf : %lu\n", workload_name[workload], memory, avg_time / (double) j, avg_iterations / j);
	}

	map_terminate();

	free(ts);

	return 0;
}
