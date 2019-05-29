#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include "../include/spinlock.h"

static spinlock_t threads_lock = SPINLOCK_INIT;

int main(){

	omp_set_num_threads(4);
	#pragma omp parallel
	{
		spinlock_lock(&threads_lock);
		printf("thread %d of %d get token for 2 secs\n", omp_get_thread_num(), omp_get_num_threads());
		sleep(2);
		spinlock_unlock(&threads_lock);
	}

	return 0;
}