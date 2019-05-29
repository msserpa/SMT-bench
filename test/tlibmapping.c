#include <stdio.h>
#include <stdlib.h>
#include "../include/mixed.h"
#include "../include/libmapping.h"

extern thread_data_t *threads;
extern uint32_t nt;

int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr, "Usage: %s <mapping>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	map_env(argv[1]);

	if(getenv("OMP_NUM_THREADS"))
		printf("OMP_NUM_THREADS=%s\n", getenv("OMP_NUM_THREADS"));
	else
		printf("missing OMP_NUM_THREADS\n");
	
	if(getenv("GOMP_CPU_AFFINITY"))
		printf("GOMP_CPU_AFFINITY=%s\n", getenv("GOMP_CPU_AFFINITY"));
	else
		printf("missing GOMP_CPU_AFFINITY\n");

	free(threads);

	return 0;
}