#ifndef WORKLOADS_H
	#define WORKLOADS_H
	#define CACHE_LINE_SIZE 128
	#define NWORKLOADS 23

	static char *workload_name[] = {
		"ctl-complex",
		"ctl-conditional",
		"ctl-random",
		"ctl-small-bbl",
		"ctl-switch",
		"dep-chain1",
		"dep-chain2",
		"dep-chain3",
		"dep-chain4",
		"dep-chain5",
		"dep-chain6",
		"fp-add",
		"fp-div",
		"fp-mul",
		"int-add",
		"int-div",
		"int-mul",
		"load-dep",
		"load-ind",
		"load-rand",
		"store-ind",
		"store-rand",
		"idle"
	};

	typedef enum workload_t{
		CONTROL_COMPLEX,
		CONTROL_CONDITIONAL,
		CONTROL_RANDOM,
		CONTROL_SMALL_BBL,
		CONTROL_SWITCH,
		DEPENDENCY_CHAIN1,
		DEPENDENCY_CHAIN2,
		DEPENDENCY_CHAIN3,
		DEPENDENCY_CHAIN4,
		DEPENDENCY_CHAIN5,
		DEPENDENCY_CHAIN6,
		EXECUTION_FP_ADD_IND,
		EXECUTION_FP_DIV_IND,
		EXECUTION_FP_MUL_IND,
		EXECUTION_INT_ADD_IND,
		EXECUTION_INT_DIV_IND,
		EXECUTION_INT_MUL_IND,
		MEMORY_LOAD_DEP,
		MEMORY_LOAD_IND,
		MEMORY_LOAD_RANDOM,
		MEMORY_STORE_IND,
		MEMORY_STORE_RANDOM,
		WORKLOAD_IDLE
	}workload_t;

	typedef struct list_t{
		uint64_t v;
		struct list_t *next;
	} __attribute__ ((aligned (CACHE_LINE_SIZE))) list_t;

	typedef struct vec_t{
		uint64_t v;
	} __attribute__ ((aligned (CACHE_LINE_SIZE))) vec_t;

	typedef struct thread_data_t{
		workload_t typeA, typeB;
		uint32_t cpu;
		uint64_t loops;
		pid_t tid;

		char *event;
		int EventSet1;
		long long value[2];
		uint64_t overflows;

		uint64_t v2;
		// uint64_t *buffer;
		// double *A, *B, *C;
		list_t *ptr_list;
		vec_t *ptr_vec;
		uint64_t memoryA, memoryB; // in KB
	}  __attribute__ ((aligned (CACHE_LINE_SIZE))) thread_data_t;

	void (*work[NWORKLOADS]) (thread_data_t *t);
	void init_workload();
	void control_complex(thread_data_t *t);
	void control_conditional(thread_data_t *t);
	void control_random(thread_data_t *t);
	void control_small_bbl(thread_data_t *t);
	void control_switch(thread_data_t *t);
	void dependency_chain1(thread_data_t *t);
	void dependency_chain2(thread_data_t *t);
	void dependency_chain3(thread_data_t *t);
	void dependency_chain4(thread_data_t *t);
	void dependency_chain5(thread_data_t *t);
	void dependency_chain6(thread_data_t *t);
	void execution_fp_add_ind(thread_data_t *t);
	void execution_fp_div_ind(thread_data_t *t);
	void execution_fp_mul_ind(thread_data_t *t);
	void execution_int_add_ind(thread_data_t *t);
	void execution_int_div_ind(thread_data_t *t);
	void execution_int_mul_ind(thread_data_t *t);
	void alloc_list(thread_data_t *t);
	void memory_load_dep(thread_data_t *t);
	void alloc_vec(thread_data_t *t);
	void init_vec(thread_data_t *t);
	void memory_load_ind(thread_data_t *t);
	void memory_load_random(thread_data_t *t);
	void memory_store_ind(thread_data_t *t);
	void memory_store_random(thread_data_t *t);
	void workload_idle(thread_data_t *t);
#endif