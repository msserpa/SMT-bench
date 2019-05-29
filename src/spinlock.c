#include "../include/spinlock.h"

void spinlock_lock(spinlock_t *exclusion){
	while(__sync_lock_test_and_set(exclusion, 1))
		CPU_PAUSE
}

void spinlock_unlock(spinlock_t *exclusion){
	__sync_synchronize();
	__sync_lock_release(exclusion);
}