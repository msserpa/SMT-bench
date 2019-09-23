#ifndef SPINLOCK_H

	#define SPINLOCK_H
	#define SPINLOCK_INIT 0
	
	#if defined(__x86_64__)
		#define CPU_PAUSE __asm__ __volatile__ ("pause");	
	#endif

	typedef int spinlock_t;

	void spinlock_lock(spinlock_t *exclusion);

	void spinlock_unlock(spinlock_t *exclusion);

#endif