#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#ifndef MIXED_H
	#define MIXED_H

	#include <stdint.h>
	#include <sys/types.h>
	#include "workloads.h"

	void libmapping_set_aff_thread(pid_t pid, uint64_t cpu);
	void *pthreads_callback(void *data);
	void *time_monitor(void *walltime);
	int isInt(char *str);
	void parse_type_vector(const char *argv, char class);

#endif