#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/workloads.h"
#include "../include/mixed.h"
#include "../include/mypapi.h"
#include "../include/libmapping.h"

uint32_t papi_enabled = 0;
extern thread_data_t *threads;
extern uint32_t nt;

int main(int argc, char **argv){
	printf("PAPI-based microarchitectural benchmark\n\n");
	uint64_t i;
	uint64_t loops[NWORKLOADS];
	pthread_t *ts;

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
					
		printf("%s(%d)", workload_name[threads[i].typeA], threads[i].cpu);
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

	for(i = 0; i < NWORKLOADS; i++)
		loops[i] = 0;

	for(i = 0; i < nt; i++)
		loops[threads[i].typeA] += threads[i].loops;

	for(i = 0; i < NWORKLOADS; i++)
		if(loops[i] != 0)
			fprintf(stderr, "%s:%llu\n", workload_name[i], loops[i]);

	map_terminate();

	free(ts);

	return 0;
}