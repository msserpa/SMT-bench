#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "../include/mixed.h"
#include "../include/mypapi.h"
#include "../include/workloads.h"

volatile int alive = 1;
thread_data_t *threads = NULL;
uint32_t nt = 0, nt_exec = 0, freq_time_ms = 1;
extern uint32_t papi_enabled;
extern uint32_t os_enabled;
extern char log_dir[BUFFER_SIZE];

void *freq_monitor(void *data){
	printf("freq monitor!\n");
	freq_thread_data_t *f = (freq_thread_data_t *) data;
	char buffer[BUFFER_SIZE];
	size_t read;
	FILE *fr, *fw;

	sprintf(buffer, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", f->cpu);
	fr = fopen(buffer, "r");

	sprintf(buffer, "%s/%s.%d.freq", log_dir, workload_name[f->type], f->cpu);
	fw = fopen(buffer, "w");
	
	fprintf(fw, "%lu\n", (unsigned long) time(NULL));
	while(alive){
		read = fread(buffer, 1, BUFFER_SIZE - 1, fr);
		buffer[read] = '\0';
		fseek(fr, 0, SEEK_SET);
		fwrite(buffer, 1, read, fw);
		usleep((uint64_t) freq_time_ms * 1000);
	}

	fclose(fr);
	fclose(fw);

	pthread_exit(NULL);
}

void *time_monitor(void *walltime){
	usleep((uint64_t) walltime * 1000000);
	alive = 0;
	pthread_exit(NULL);
}

void libmapping_set_aff_thread(pid_t pid, uint64_t cpu){
	#if defined(linux) || defined (__linux)
		uint32_t ret;
		cpu_set_t mask;

		CPU_ZERO(&mask);
		CPU_SET(cpu, &mask);

		errno = 0;
		ret = sched_setaffinity(pid, sizeof(mask), &mask);
		if(errno != 0){
			printf("libmapping error, cannot bind to CPU %ld - ret:%d\n", cpu, ret);
			switch(errno){
				case EFAULT:
					printf("error: EFAULT\n");
				break;
				case EINVAL:
					printf("error: EINVAL\n");
				break;
				case EPERM:
					printf("error: EPERM\n");
				break;
				case ESRCH:
					printf("error: ESRCH\n");
				break;
				default:
					printf("error: unknown\n");
			}
		}
	#else
		#error Only linux is supported at the moment
	#endif
}

double get_time(){
   struct timespec tp;
   clock_gettime(CLOCK_MONOTONIC, &tp);
   return (double) tp.tv_sec + (double) tp.tv_nsec / 10E9;
}

void *pthreads_callback (void *data){
	thread_data_t *t = (thread_data_t*) data;
	t->tid = syscall(__NR_gettid);
	
	if(!os_enabled)
		libmapping_set_aff_thread(t->tid, t->cpu);
	
	if(papi_enabled && t->typeA != WORKLOAD_IDLE)
		papi_thread_init(t);


	pthread_t thread_freq;
	freq_thread_data_t f;
	f.cpu = t->cpu;
	f.type = t->typeA;
	pthread_create(&thread_freq, NULL, freq_monitor, (void *) &f);

	double start = get_time();

	(*work[t->typeA]) (t);
	
	double end = get_time();
	t->time = end - start;

	pthread_join(thread_freq, NULL);

	if(papi_enabled && t->typeA != WORKLOAD_IDLE)
		papi_thread_finish(t);

	pthread_exit(NULL);
}

int isInt(char *str){
	char *p;
	for(p = str; *p; p++)
		if(!isdigit(*p))
			return 0;
	return 1;
}

void parse_type_vector(const char *argv){
	uint64_t *memory, i, j, n, size = strlen(argv);
	char *str, *token;
	workload_t *workload;
	const char *comma = ",";

	str = (char *) malloc((size + 1) * sizeof(char));
	strcpy(str, argv);

	n = 1;
	for(i = 0; i < size; i++)
		if(str[i] == ',')
			n++;
		else if(str[i] == ':')
			str[i] = ',';

	workload = (workload_t *) malloc(n * sizeof(workload_t));
	assert(workload != NULL);

	memory = (uint64_t *) calloc(n, sizeof(uint64_t *));
	assert(memory != NULL);

	i = 0;
	token = strtok(str, comma);
	while(token != NULL){
		if(isInt((token))){
			memory[i - 1] = atoi(token);
			if(memory[i - 1] < 1){
				printf("The array length needs be at least 1024 %s\n", token);
				exit(EXIT_FAILURE);				
			}
		}
		else{
			for(j = 0; j < NWORKLOADS; j++)
				if(strcmp(token, workload_name[j]) == 0){
					workload[i++] = (workload_t) j;
					break;
				}
			if(j == NWORKLOADS){
				printf("wrong type %s\n", token);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, comma);
	}
	free(str);
	assert(i == n);

	for(i = 0; i < nt_exec; i++){
		threads[i].typeA  = workload[i % n];
		threads[i].memoryA = memory[i % n];
		threads[i].typeB = workload[(i + 1) % n];
		threads[i].memoryB = memory[(i + 1) % n];
	}

	free(workload);
	free(memory);
}