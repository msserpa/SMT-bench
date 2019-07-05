#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "../include/libmapping.h"
#include "../include/mixed.h"

extern thread_data_t *threads;
extern uint32_t nt;
char *map, *env_omp, *env_mapping;

void error_handler(const char *call, const int line){
	fprintf(stderr, "\nlibmapping:%d - %s\n\n", line, call);
	exit(EXIT_FAILURE);	
}

void map_init(){
	char *command = "lstopo-no-graphics --no-caches --no-io -p > /tmp/hwloc; sleep 1";
	

	if(system(command) != 0)
		error_handler("hwloc-ls not found!", __LINE__);
}

void map_terminate(){
	free(threads);
	free(map);
	free(env_omp);
	free(env_mapping);
}

void map_threads(){
	FILE *f;
	char *line, *str;

	f = fopen("/tmp/hwloc", "r");
	if(f == NULL)
		error_handler("File not found!", __LINE__);

	line = (char *) malloc(BUFFER_SIZE * sizeof(char));
	while(fgets(line, BUFFER_SIZE, f) != NULL){
		str = strstr(line, "PU P#");
		if(str)
			nt++;
	}
	free(line);

	env_omp = (char *) calloc(BUFFER_SIZE,  sizeof(char));
	sprintf(env_omp, "OMP_NUM_THREADS=%d", nt);

	env_omp = (char *) realloc(env_omp, (strlen(env_omp) + 1) * sizeof(char));
	putenv(env_omp);

	fclose(f);
}

void map_heterogeneous(){
	FILE *f;
	uint32_t *app_heterogeneous, i = 0;
	char *line, *env_heterogeneous, *str;

	app_heterogeneous = (uint32_t *)  malloc(nt * sizeof(uint32_t));

	f = fopen("/tmp/hwloc", "r");
	if(f == NULL)
		error_handler("File not found!", __LINE__);

	line = (char *) malloc(BUFFER_SIZE * sizeof(char));
	while(fgets(line, BUFFER_SIZE, f) != NULL){
		str = strstr(line, "PU P#");
		if(str != NULL)
			app_heterogeneous[i++] = atoi(str += strlen("PU P#"));
	}
	free(line);
	fclose(f);

	env_heterogeneous = (char *) calloc(BUFFER_SIZE,  sizeof(char));
	sprintf(env_heterogeneous, "GOMP_CPU_AFFINITY=");

	for(i = 0; i < nt - 1; i++)
		sprintf(&env_heterogeneous[strlen(env_heterogeneous)], "%d,", app_heterogeneous[i]);
	sprintf(&env_heterogeneous[strlen(env_heterogeneous)], "%d", app_heterogeneous[nt - 1]);
	
	for(i = 0; i < nt; i++)
		threads[i].cpu = app_heterogeneous[i];

	env_heterogeneous = (char *) realloc(env_heterogeneous, (strlen(env_heterogeneous) + 1) * sizeof(char));
	putenv(env_heterogeneous);	
	env_mapping = env_heterogeneous;

	free(app_heterogeneous);
}

void map_homogeneos(){
	FILE *f;
	uint32_t *app_homogeneos, i, j = 0;
	char *line, *env_homogeneos, *str;

	app_homogeneos = (uint32_t *)  malloc(nt * sizeof(uint32_t));

	f = fopen("/tmp/hwloc", "r");
	if(f == NULL)
		error_handler("File not found!", __LINE__);

	line = (char *) malloc(BUFFER_SIZE * sizeof(char));
	i = 0;
	while(fgets(line, BUFFER_SIZE, f) != NULL){
		str = strstr(line, "PU P#");
		if(str != NULL){
			if(i % 2 == 0)
				app_homogeneos[j++] = atoi(str += strlen("PU P#"));
			i++;
		}
	}

	fseek(f, 0, SEEK_SET);
	i = 0;
	while(fgets(line, BUFFER_SIZE, f) != NULL){
		str = strstr(line, "PU P#");
		if(str != NULL){
			if(i % 2 == 1)
				app_homogeneos[j++] = atoi(str += strlen("PU P#"));
			i++;
		}
	}
	free(line);
	fclose(f);

	env_homogeneos = (char *) calloc(BUFFER_SIZE,  sizeof(char));
	sprintf(env_homogeneos, "GOMP_CPU_AFFINITY=");

	for(i = 0; i < nt - 1; i++)
		sprintf(&env_homogeneos[strlen(env_homogeneos)], "%d,", app_homogeneos[i]);
	sprintf(&env_homogeneos[strlen(env_homogeneos)], "%d", app_homogeneos[nt - 1]);

	for(i = 0; i < nt; i++)
		threads[i].cpu = app_homogeneos[i];

	env_homogeneos = (char *) realloc(env_homogeneos, (strlen(env_homogeneos) + 1) * sizeof(char));
	putenv(env_homogeneos);	
	env_mapping = env_homogeneos;

	free(app_homogeneos);
}

void map_random(){
	char *env_random;
	uint32_t i, *app_random, *app_aux, aux_rand;

	srand(time(0));

	app_random = (uint32_t *)  malloc(nt * sizeof(uint32_t));
	app_aux	   = (uint32_t *)  calloc(nt,  sizeof(uint32_t));

	for(i = 0; i < nt; i++){
		do{
			aux_rand = rand() % nt;
		}while(app_aux[aux_rand] == 1);
		app_aux[aux_rand] = 1;
		app_random[i] = aux_rand;
	}

	env_random = (char *) calloc(BUFFER_SIZE, sizeof(char));
	sprintf(env_random, "GOMP_CPU_AFFINITY=");

	for(i = 0; i < nt - 1; i++)
		sprintf(&env_random[strlen(env_random)], "%d,", app_random[i]);
	sprintf(&env_random[strlen(env_random)], "%d", app_random[nt - 1]);

	for(i = 0; i < nt; i++)
		threads[i].cpu = app_random[i];

	env_random = (char *) realloc(env_random, (strlen(env_random) + 1) * sizeof(char));
	putenv(env_random);
	env_mapping = env_random;

	free(app_random);
	free(app_aux);
}

void thread_init(){
	uint32_t i;

	threads = (thread_data_t *) malloc(nt * sizeof(thread_data_t));
	assert(threads != NULL);
	
	for(i = 0; i < nt; i++){
		threads[i].typeA = WORKLOAD_IDLE;
		threads[i].typeB = WORKLOAD_IDLE;
		threads[i].cpu = -1;
		threads[i].loops = 0;
		threads[i].tid = -1;
		threads[i].event = NULL;
		threads[i].EventSet1 = 0;
		threads[i].value[0] = 0;
		threads[i].value[1] = 0;
		threads[i].v2 = 0;
		threads[i].ptr_list = NULL;
		threads[i].ptr_vec = NULL;
		threads[i].memoryA = 0;
		threads[i].memoryB = 0;
	}	
}

void map_env(char *mapping){
	map_init();
	map_threads();
	thread_init();	

	map = (char *) calloc(BUFFER_SIZE, sizeof(char));

	if(mapping[0] == 'h' && mapping[1] == 'e'){
		strcpy(map, "hetero");
		map_heterogeneous();
	}
	else if(mapping[0] == 'h' && mapping[1] == 'o'){
		strcpy(map, "homo");
		map_homogeneos();
	}
	else{
		strcpy(map, "rand");
		map_random();
	}
	map = (char *) realloc(map, (strlen(map) + 1) * sizeof(char));
}