#ifndef WORKLOADS_H
	#define WORKLOADS_H
	#define CACHE_LINE_SIZE 128
	#define NWORKLOADS 68
	#define PAPI_MAX_EVENTS 1

	#ifndef BUFFER_SIZE
		#define BUFFER_SIZE 1024
	#endif

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-variable"
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
		"idle",
		"ucomis_clean",
		"ucomis_dirty",
		"scalar_iadd",
		"avx128_iadd",
		"avx256_iadd",
		"avx512_iadd",
		"avx128_iadd16",
		"avx256_iadd16",
		"avx512_iadd16",
		"avx128_iadd_t",
		"avx256_iadd_t",
		"avx128_mov_sparse",
		"avx256_mov_sparse",
		"avx512_mov_sparse",
		"avx128_merge_sparse",
		"avx256_merge_sparse",
		"avx512_merge_sparse",
		"avx128_vshift",
		"avx256_vshift",
		"avx512_vshift",
		"avx128_vshift_t",
		"avx256_vshift_t",
		"avx512_vshift_t",
		"avx128_vlzcnt",
		"avx256_vlzcnt",
		"avx512_vlzcnt",
		"avx128_vlzcnt_t",
		"avx256_vlzcnt_t",
		"avx512_vlzcnt_t",
		"avx128_imul",
		"avx256_imul",
		"avx512_imul",
		"avx128_fma_sparse",
		"avx256_fma_sparse",
		"avx512_fma_sparse",
		"avx128_fma",
		"avx256_fma",
		"avx512_fma",
		"avx128_fma_t",
		"avx256_fma_t",
		"avx512_fma_t",
		"avx512_vpermw",
		"avx512_vpermw_t",
		"avx512_vpermd",
		"avx512_vpermd_t"
	};
	#pragma GCC diagnostic pop

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
		WORKLOAD_IDLE,
		UCOMIS_CLEAN,
		UCOMIS_DIRTY,
		SCALAR_IADD,
		AVX128_IADD,
		AVX256_IADD,
		AVX512_IADD,
		AVX128_IADD16,
		AVX256_IADD16,
		AVX512_IADD16,
		AVX128_IADD_T,
		AVX256_IADD_T,
		AVX128_MOV_SPARSE,
		AVX256_MOV_SPARSE,
		AVX512_MOV_SPARSE,
		AVX128_MERGE_SPARSE,
		AVX256_MERGE_SPARSE,
		AVX512_MERGE_SPARSE,
		AVX128_VSHIFT,
		AVX256_VSHIFT,
		AVX512_VSHIFT,
		AVX128_VSHIFT_T,
		AVX256_VSHIFT_T,
		AVX512_VSHIFT_T,
		AVX128_VLZCNT,
		AVX256_VLZCNT,
		AVX512_VLZCNT,
		AVX128_VLZCNT_T,
		AVX256_VLZCNT_T,
		AVX512_VLZCNT_T,
		AVX128_IMUL,
		AVX256_IMUL,
		AVX512_IMUL,
		AVX128_FMA_SPARSE,
		AVX256_FMA_SPARSE,
		AVX512_FMA_SPARSE,
		AVX128_FMA,
		AVX256_FMA,
		AVX512_FMA,
		AVX128_FMA_T,
		AVX256_FMA_T,
		AVX512_FMA_T,
		AVX512_VPERMW,
		AVX512_VPERMW_T,
		AVX512_VPERMD,
		AVX512_VPERMD_T
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
		uint64_t iterations;
		double time;
		pid_t tid;

		int32_t EventSet1;
		long long value[PAPI_MAX_EVENTS];

		uint64_t v2;
		list_t *ptr_list;
		vec_t *ptr_vec;
		uint64_t memoryA, memoryB; // in KB
	}  __attribute__ ((aligned (CACHE_LINE_SIZE))) thread_data_t;

	typedef struct freq_thread_data_t{
		workload_t type;
		uint32_t cpu;
	}  __attribute__ ((aligned (CACHE_LINE_SIZE))) freq_thread_data_t;

	extern void (*work[NWORKLOADS]) (thread_data_t *t);
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
	void free_list(thread_data_t *t);
	void memory_load_dep(thread_data_t *t);
	void alloc_vec(thread_data_t *t);
	void free_vec(thread_data_t *t);
	void init_vec(thread_data_t *t);
	void memory_load_ind(thread_data_t *t);
	void memory_load_random(thread_data_t *t);
	void memory_store_ind(thread_data_t *t);
	void memory_store_random(thread_data_t *t);
	void workload_idle(thread_data_t *t);
	void h_ucomis_clean(thread_data_t *t);
	void h_ucomis_dirty(thread_data_t *t);
	void h_scalar_iadd(thread_data_t *t);
	void h_avx128_iadd(thread_data_t *t);
	void h_avx256_iadd(thread_data_t *t);
	void h_avx512_iadd(thread_data_t *t);
	void h_avx128_iadd16(thread_data_t *t);
	void h_avx256_iadd16(thread_data_t *t);
	void h_avx512_iadd16(thread_data_t *t);
	void h_avx128_iadd_t(thread_data_t *t);
	void h_avx256_iadd_t(thread_data_t *t);
	void h_avx128_mov_sparse(thread_data_t *t);
	void h_avx256_mov_sparse(thread_data_t *t);
	void h_avx512_mov_sparse(thread_data_t *t);
	void h_avx128_merge_sparse(thread_data_t *t);
	void h_avx256_merge_sparse(thread_data_t *t);
	void h_avx512_merge_sparse(thread_data_t *t);
	void h_avx128_vshift(thread_data_t *t);
	void h_avx256_vshift(thread_data_t *t);
	void h_avx512_vshift(thread_data_t *t);
	void h_avx128_vshift_t(thread_data_t *t);
	void h_avx256_vshift_t(thread_data_t *t);
	void h_avx512_vshift_t(thread_data_t *t);
	void h_avx128_vlzcnt(thread_data_t *t);
	void h_avx256_vlzcnt(thread_data_t *t);
	void h_avx512_vlzcnt(thread_data_t *t);
	void h_avx128_vlzcnt_t(thread_data_t *t);
	void h_avx256_vlzcnt_t(thread_data_t *t);
	void h_avx512_vlzcnt_t(thread_data_t *t);
	void h_avx128_imul(thread_data_t *t);
	void h_avx256_imul(thread_data_t *t);
	void h_avx512_imul(thread_data_t *t);
	void h_avx128_fma_sparse(thread_data_t *t);
	void h_avx256_fma_sparse(thread_data_t *t);
	void h_avx512_fma_sparse(thread_data_t *t);
	void h_avx128_fma(thread_data_t *t);
	void h_avx256_fma(thread_data_t *t);
	void h_avx512_fma(thread_data_t *t);
	void h_avx128_fma_t(thread_data_t *t);
	void h_avx256_fma_t(thread_data_t *t);
	void h_avx512_fma_t(thread_data_t *t);
	void h_avx512_vpermw(thread_data_t *t);
	void h_avx512_vpermw_t(thread_data_t *t);
	void h_avx512_vpermd(thread_data_t *t);
	void h_avx512_vpermd_t(thread_data_t *t);
#endif