#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/mixed.h"
#include "../include/workloads.h"

extern int alive;

void init_workload(){
	uint64_t i = 0;
	work[i++] = control_complex;
	work[i++] = control_conditional;
	work[i++] = control_random;
	work[i++] = control_small_bbl;
	work[i++] = control_switch;
	work[i++] = dependency_chain1;
	work[i++] = dependency_chain2;
	work[i++] = dependency_chain3;
	work[i++] = dependency_chain4;
	work[i++] = dependency_chain5;
	work[i++] = dependency_chain6;
	work[i++] = execution_fp_add_ind;
	work[i++] = execution_fp_div_ind;
	work[i++] = execution_fp_mul_ind;
	work[i++] = execution_int_add_ind;
	work[i++] = execution_int_div_ind;
	work[i++] = execution_int_mul_ind;
	work[i++] = memory_load_dep;
	work[i++] = memory_load_ind;
	work[i++] = memory_load_random;
	work[i++] = memory_store_ind;
	work[i++] = memory_store_random;
	work[i++] = workload_idle;
}

void control_complex(thread_data_t *t){
	uint64_t i = 0, j = -1, k = 2, l = 3, m = -1, n = 5,o = 6;

	do{
		if(i % 2 == 0){
			j++;
			switch(j & 3){
				case 0:
				case 1:
					k++;
				break;
				case 2:
				case 3:
					l++;
				break;
			}
		}else{
			m++;
			switch(m & 7){
				case 0:
				case 1:
				case 2:
				case 3:
					n++;
				break;
				case 4:
				case 5:
				case 6:
				case 7:
					o++;
				break;
			}
		}
		i++;
	}while(alive);

	t->v2 = k;
	t->loops = i;
}

void control_conditional(thread_data_t *t){
	uint64_t i = 0, jump = 1, print = 0;

	do{
		if(jump){
			jump = 0;
			print += i;
		}else{
			jump = 1;
			print -= i;
		}
		i++;
	}while(alive);

	t->v2 = print;
	t->loops = i;
}

void control_random(thread_data_t *t){
	uint64_t i = 0, jump = 1, lfsr = 0x80000000, bit;

	do{
		// Linear Feedback Shift Register
		bit  = ~((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 11) ^ (lfsr >> 30) ) & 1;
		lfsr = (lfsr >> 1) | (bit << 31);
		jump = lfsr & 1;
		if(jump)
			asm volatile("mov %0, %0" : "=r" (bit) : "r" (bit) : );
		else
			asm volatile("mov %0, %0" : "=r" (lfsr) : "r" (lfsr) : );

		bit  = ~((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 11) ^ (lfsr >> 30) ) & 1;
		lfsr = (lfsr >> 1) | (bit << 31);
		jump = lfsr & 1;
		if(jump)
			asm volatile("mov %0, %0" : "=r" (bit) : "r" (bit) : );
		else
			asm volatile("mov %0, %0" : "=r" (lfsr) : "r" (lfsr) : );

		bit  = ~((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 11) ^ (lfsr >> 30) ) & 1;
		lfsr = (lfsr >> 1) | (bit << 31);
		jump = lfsr & 1;
		if(jump)
			asm volatile("mov %0, %0" : "=r" (bit) : "r" (bit) : );
		else
			asm volatile("mov %0, %0" : "=r" (lfsr) : "r" (lfsr) : );

		bit  = ~((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 11) ^ (lfsr >> 30) ) & 1;
		lfsr = (lfsr >> 1) | (bit << 31);
		jump = lfsr & 1;
		if(jump)
			asm volatile("mov %0, %0" : "=r" (bit) : "r" (bit) : );
		else
			asm volatile("mov %0, %0" : "=r" (lfsr) : "r" (lfsr) : );								

		i++;
	}while(alive);

	t->v2 = bit;
	t->loops = i;
}

void control_small_bbl(thread_data_t *t){
	uint64_t i = 0, j, print = 0, count[64];
   
   	for(j = 0; j < 64; j++)
        count[j] = 0;

	do{
		i++;
	}while(alive);
	
	for(j = 0; j < 64; j++)
		print += count[j];

	t->v2 = print;
	t->loops = i;
}

void control_switch(thread_data_t *t){
	uint64_t i = 0, inner_repetitions = 4E10;
	uint64_t jump = 1, print = 1;
    uint64_t jump_1  = inner_repetitions *  1;
    uint64_t jump_2  = inner_repetitions *  2;
    uint64_t jump_3  = inner_repetitions *  3;
    uint64_t jump_4  = inner_repetitions *  4;
    uint64_t jump_5  = inner_repetitions *  5;
    uint64_t jump_6  = inner_repetitions *  6;
    uint64_t jump_7  = inner_repetitions *  7;
    uint64_t jump_8  = inner_repetitions *  8;
    uint64_t jump_9  = inner_repetitions *  9;
    uint64_t jump_10 = inner_repetitions * 10;

	do{
		switch(jump){
			case 1:
				if(i > jump_1)
					jump++;
				print += 1;
			break;
			case 2:
				if(i > jump_2)
					jump++;
				print += 2;
			break;
			case 3:
				if(i > jump_3)
					jump++;
				print += 3;
			break;
			case 4:
				if(i > jump_4)
					jump++;
				print += 4;
			break;
			case 5:
				if(i > jump_5)
					jump++;
				print += 5;
			break;
			case 6:
				if(i > jump_6)
					jump++;
				print += 6;
			break;
			case 7:
				if(i > jump_7)
					jump++;
				print += 7;
			break;
			case 8:
				if(i > jump_8)
					jump++;
				print += 8;
			break;
			case 9:
				if(i > jump_9)
					jump++;
				print += 9;
			break;
			case 10:
				if(i > jump_10)
					jump++;
				print += 10;
			break;
			default:
				fprintf(stderr, "Please provide the correct number of inner-repetitions.\n");
				exit(EXIT_FAILURE);
		}
		i++;
	}while(alive);

	t->v2 = print;
	t->loops = i;
}

void dependency_chain1(thread_data_t *t){
	uint64_t i = 0, count0 = 0;

	do{
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		i++;
	}while(alive);

	t->v2 = count0;
	t->loops = i;
}

void dependency_chain2(thread_data_t *t){
	uint64_t i = 0, count0 = 0, count1 = 0;

	do{
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		i++;
	}while(alive);

	t->v2 = count1;
	t->loops = i;
}


void dependency_chain3(thread_data_t *t){
	uint64_t i = 0, count0 = 0, count1 = 0, count2 = 0;

	do{
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		i++;
	}while(alive);

	t->v2 = count2;
	t->loops = i;
}

void dependency_chain4(thread_data_t *t){
	uint64_t i = 0, count0 = 0, count1 = 0, count2 = 0, count3 = 0;

	do{
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		i++;
	}while(alive);

	t->v2 = count3;
	t->loops = i;
}

void dependency_chain5(thread_data_t *t){
	uint64_t i = 0, count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;

	do{
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		i++;
	}while(alive);

	t->v2 = count4;
	t->loops = i;
}

void dependency_chain6(thread_data_t *t){
	uint64_t i = 0, count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;

	do{
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );
		i++;
	}while(alive);

	t->v2 = count5;
	t->loops = i;
}

void execution_fp_add_ind(thread_data_t *t){
	uint64_t i = 0;
	double count = 0.00, in = 0.00;

	asm volatile("push %0"::"r"(in):);

	asm volatile("subsd %%xmm0, %%xmm0" : : : "xmm0");
	asm volatile("subsd %%xmm1, %%xmm1" : : : "xmm1");
	asm volatile("subsd %%xmm2, %%xmm2" : : : "xmm2");
	asm volatile("subsd %%xmm3, %%xmm3" : : : "xmm3");
	asm volatile("subsd %%xmm4, %%xmm4" : : : "xmm4");
	asm volatile("subsd %%xmm5, %%xmm5" : : : "xmm5");
	asm volatile("subsd %%xmm6, %%xmm6" : : : "xmm6");
	asm volatile("subsd %%xmm7, %%xmm7" : : : "xmm7");

	asm volatile("movsd (%%rsp), %%xmm0" : : : "xmm0");
	asm volatile("movsd (%%rsp), %%xmm1" : : : "xmm1");
	asm volatile("movsd (%%rsp), %%xmm2" : : : "xmm2");
	asm volatile("movsd (%%rsp), %%xmm3" : : : "xmm3");
	asm volatile("movsd (%%rsp), %%xmm4" : : : "xmm4");
	asm volatile("movsd (%%rsp), %%xmm5" : : : "xmm5");
	asm volatile("movsd (%%rsp), %%xmm6" : : : "xmm6");
	asm volatile("movsd (%%rsp), %%xmm7" : : : "xmm7");

	asm volatile("pop %%rbx" : : : "rbx");

	do{
		asm volatile("addsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("addsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("addsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("addsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("addsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("addsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("addsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("addsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("addsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("addsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("addsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("addsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("addsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("addsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("addsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("addsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("addsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("addsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("addsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("addsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("addsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("addsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("addsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("addsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("addsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("addsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("addsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("addsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("addsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("addsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("addsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("addsd %%xmm7, %%xmm7" : : : "xmm7");
		i++;
	}while(alive);

    asm volatile("push $0x0":::);
    asm volatile("movsd %%xmm0, (%%rsp)" : : : );
    asm volatile("mov (%%rsp), %0" : "=r"(count) : : );
    asm volatile("pop %%rbx" : : : "rbx");	

	t->v2 = count;
	t->loops = i;
}

void execution_fp_div_ind(thread_data_t *t){
	uint64_t i = 0;
	double count = 0.00, in = 1.00;

	asm volatile("push %0"::"r"(in):);
	asm volatile("subsd %%xmm0, %%xmm0" : : : "xmm0");
	asm volatile("subsd %%xmm1, %%xmm1" : : : "xmm1");
	asm volatile("subsd %%xmm2, %%xmm2" : : : "xmm2");
	asm volatile("subsd %%xmm3, %%xmm3" : : : "xmm3");
	asm volatile("subsd %%xmm4, %%xmm4" : : : "xmm4");
	asm volatile("subsd %%xmm5, %%xmm5" : : : "xmm5");
	asm volatile("subsd %%xmm6, %%xmm6" : : : "xmm6");
	asm volatile("subsd %%xmm7, %%xmm7" : : : "xmm7");

	asm volatile("movsd (%%rsp), %%xmm0" : : : "xmm0");
	asm volatile("movsd (%%rsp), %%xmm1" : : : "xmm1");
	asm volatile("movsd (%%rsp), %%xmm2" : : : "xmm2");
	asm volatile("movsd (%%rsp), %%xmm3" : : : "xmm3");
	asm volatile("movsd (%%rsp), %%xmm4" : : : "xmm4");
	asm volatile("movsd (%%rsp), %%xmm5" : : : "xmm5");
	asm volatile("movsd (%%rsp), %%xmm6" : : : "xmm6");
	asm volatile("movsd (%%rsp), %%xmm7" : : : "xmm7");

	asm volatile("pop %%rbx" : : : "rbx");

	do{
		asm volatile("divsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("divsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("divsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("divsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("divsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("divsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("divsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("divsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("divsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("divsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("divsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("divsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("divsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("divsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("divsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("divsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("divsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("divsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("divsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("divsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("divsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("divsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("divsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("divsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("divsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("divsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("divsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("divsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("divsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("divsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("divsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("divsd %%xmm7, %%xmm7" : : : "xmm7");
		i++;
	}while(alive);

    asm volatile("push $0x0":::);
    asm volatile("movsd %%xmm0, (%%rsp)" : : : );
    asm volatile("mov (%%rsp), %0" : "=r"(count) : : );
    asm volatile("pop %%rbx" : : : "rbx");

	t->v2 = count;
	t->loops = i;
}

void execution_fp_mul_ind(thread_data_t *t){
	uint64_t i = 0;
	double count = 0.00, in = 1.00;

	asm volatile("push %0"::"r"(in):);

	asm volatile("subsd %%xmm0, %%xmm0" : : : "xmm0");
	asm volatile("subsd %%xmm1, %%xmm1" : : : "xmm1");
	asm volatile("subsd %%xmm2, %%xmm2" : : : "xmm2");
	asm volatile("subsd %%xmm3, %%xmm3" : : : "xmm3");
	asm volatile("subsd %%xmm4, %%xmm4" : : : "xmm4");
	asm volatile("subsd %%xmm5, %%xmm5" : : : "xmm5");
	asm volatile("subsd %%xmm6, %%xmm6" : : : "xmm6");
	asm volatile("subsd %%xmm7, %%xmm7" : : : "xmm7");

	asm volatile("movsd (%%rsp), %%xmm0" : : : "xmm0");
	asm volatile("movsd (%%rsp), %%xmm1" : : : "xmm1");
	asm volatile("movsd (%%rsp), %%xmm2" : : : "xmm2");
	asm volatile("movsd (%%rsp), %%xmm3" : : : "xmm3");
	asm volatile("movsd (%%rsp), %%xmm4" : : : "xmm4");
	asm volatile("movsd (%%rsp), %%xmm5" : : : "xmm5");
	asm volatile("movsd (%%rsp), %%xmm6" : : : "xmm6");
	asm volatile("movsd (%%rsp), %%xmm7" : : : "xmm7");

	asm volatile("pop %%rbx" : : : "rbx");

	do{
		asm volatile("mulsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("mulsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("mulsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("mulsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("mulsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("mulsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("mulsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("mulsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("mulsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("mulsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("mulsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("mulsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("mulsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("mulsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("mulsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("mulsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("mulsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("mulsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("mulsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("mulsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("mulsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("mulsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("mulsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("mulsd %%xmm7, %%xmm7" : : : "xmm7");

		asm volatile("mulsd %%xmm0, %%xmm0" : : : "xmm0");
		asm volatile("mulsd %%xmm1, %%xmm1" : : : "xmm1");
		asm volatile("mulsd %%xmm2, %%xmm2" : : : "xmm2");
		asm volatile("mulsd %%xmm3, %%xmm3" : : : "xmm3");
		asm volatile("mulsd %%xmm4, %%xmm4" : : : "xmm4");
		asm volatile("mulsd %%xmm5, %%xmm5" : : : "xmm5");
		asm volatile("mulsd %%xmm6, %%xmm6" : : : "xmm6");
		asm volatile("mulsd %%xmm7, %%xmm7" : : : "xmm7");
		i++;
	}while(alive);

    asm volatile("push $0x0":::);
    asm volatile("movsd %%xmm0, (%%rsp)" : : : );
    asm volatile("mov (%%rsp), %0" : "=r"(count) : : );
    asm volatile("pop %%rbx" : : : "rbx");

	t->v2 = count;
	t->loops = i;
}

void execution_int_add_ind(thread_data_t *t){
	uint64_t i = 0, count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0;

	do{
		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("add %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("add %0, %0" : "=r" (count7) : "0" (count7) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("add %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("add %0, %0" : "=r" (count7) : "0" (count7) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("add %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("add %0, %0" : "=r" (count7) : "0" (count7) : );

		asm volatile("add %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("add %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("add %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("add %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("add %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("add %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("add %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("add %0, %0" : "=r" (count7) : "0" (count7) : );
		i++;
	}while(alive);

	t->v2 = count7;
	t->loops = i;
}

void execution_int_div_ind(thread_data_t *t){
	uint64_t i = 0, count = 0;

	asm volatile("mov $0x0, %%rax" : : : "rax");
	asm volatile("mov $0x0, %%rdx" : : : "rdx");
	asm volatile("mov $0x1, %%rbx" : : : "rbx");

	do{
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );

		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );

		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );

		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		asm volatile("idiv %%rbx" : : : "rax", "rdx", "rbx" );
		i++;
	}while(alive);
	asm volatile("mov %%rbx, %0" : "=r"(count) : : "rbx");

	t->v2 = count;
	t->loops = i;
}

void execution_int_mul_ind(thread_data_t *t){
	uint64_t i = 0, count0 = 1, count1 = 1, count2 = 1, count3 = 1, count4 = 1, count5 = 1, count6 = 1, count7 = 1;

	do{
		asm volatile("imul %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("imul %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("imul %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("imul %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("imul %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("imul %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("imul %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("imul %0, %0" : "=r" (count7) : "0" (count7) : );

		asm volatile("imul %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("imul %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("imul %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("imul %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("imul %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("imul %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("imul %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("imul %0, %0" : "=r" (count7) : "0" (count7) : );

		asm volatile("imul %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("imul %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("imul %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("imul %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("imul %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("imul %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("imul %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("imul %0, %0" : "=r" (count7) : "0" (count7) : );

		asm volatile("imul %0, %0" : "=r" (count0) : "0" (count0) : );
		asm volatile("imul %0, %0" : "=r" (count1) : "0" (count1) : );
		asm volatile("imul %0, %0" : "=r" (count2) : "0" (count2) : );
		asm volatile("imul %0, %0" : "=r" (count3) : "0" (count3) : );
		asm volatile("imul %0, %0" : "=r" (count4) : "0" (count4) : );
		asm volatile("imul %0, %0" : "=r" (count5) : "0" (count5) : );
		asm volatile("imul %0, %0" : "=r" (count6) : "0" (count6) : );
		asm volatile("imul %0, %0" : "=r" (count7) : "0" (count7) : );
		i++;
	}while(alive);

	t->v2 = count7;
	t->loops = i;
}

void alloc_list(thread_data_t *t){

	uint64_t i, length = t->memory * 1024 / sizeof(list_t);
	list_t *ptr_this;

	if(length == 0 || length % 32 != 0){
		fprintf(stderr, "The array length needs to be divisible by 32.\n");
		exit(EXIT_FAILURE);
	}

	assert(posix_memalign((void **) &t->ptr_list, CACHE_LINE_SIZE, length * sizeof(list_t)) == 0);
	assert(t->ptr_list != NULL);

    ptr_this = t->ptr_list;
	for(i = 0; i < length; i++){
		ptr_this->v = 1;
		ptr_this->next = &t->ptr_list[i+1];
		ptr_this = ptr_this->next;
		ptr_this->next = NULL;
	}
}

void memory_load_dep(thread_data_t *t){
	uint64_t i = 0, j = 0, print = 0, length = t->memory * 1024 / sizeof(list_t);
	list_t *ptr_this;

	do{
		ptr_this = t->ptr_list;
		for(j = 0; j <= length - 32; j += 32){
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;

			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;

			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;

			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;
			ptr_this = ptr_this->next;

			print = ptr_this->v;
		}
		i += j;
	}while(alive);

	t->v2 = print;
	t->loops = i;
}

void alloc_vec(thread_data_t *t){

	uint64_t i, length = t->memory * 1024 / sizeof(vec_t);

	if(length == 0 || length % 32 != 0){
		fprintf(stderr, "The array size needs to be divisible by 32.\n");
		exit(EXIT_FAILURE);
	}

	assert(posix_memalign((void **) &t->ptr_vec, CACHE_LINE_SIZE, length * sizeof(vec_t)) == 0);
	assert(t->ptr_vec != NULL);

	for(i = 0; i < length; i++)
        t->ptr_vec[i].v = 1;
}

void init_vec(thread_data_t *t){
	uint64_t i, length = t->memory * 1024 / sizeof(vec_t);
	
	for(i = 0; i < length; i++)
		t->ptr_vec[i].v = i;
}

void memory_load_ind(thread_data_t *t){
	uint64_t i = 0, j, jump = 0, count = 0, length = t->memory * 1024 / sizeof(vec_t);

	do{
		for(j = 0; j <= length - 32; j += 32){
			count += t->ptr_vec[jump + 0].v;
			count += t->ptr_vec[jump + 1].v;
			count += t->ptr_vec[jump + 2].v;
			count += t->ptr_vec[jump + 3].v;
			count += t->ptr_vec[jump + 4].v;
			count += t->ptr_vec[jump + 5].v;
			count += t->ptr_vec[jump + 6].v;
			count += t->ptr_vec[jump + 7].v;

			count += t->ptr_vec[jump + 8].v;
			count += t->ptr_vec[jump + 9].v;
			count += t->ptr_vec[jump + 10].v;
			count += t->ptr_vec[jump + 11].v;
			count += t->ptr_vec[jump + 12].v;
			count += t->ptr_vec[jump + 13].v;
			count += t->ptr_vec[jump + 14].v;
			count += t->ptr_vec[jump + 15].v;

			count += t->ptr_vec[jump + 16].v;
			count += t->ptr_vec[jump + 17].v;
			count += t->ptr_vec[jump + 18].v;
			count += t->ptr_vec[jump + 19].v;
			count += t->ptr_vec[jump + 20].v;
			count += t->ptr_vec[jump + 21].v;
			count += t->ptr_vec[jump + 22].v;
			count += t->ptr_vec[jump + 23].v;

			count += t->ptr_vec[jump + 24].v;
			count += t->ptr_vec[jump + 25].v;
			count += t->ptr_vec[jump + 26].v;
			count += t->ptr_vec[jump + 27].v;
			count += t->ptr_vec[jump + 28].v;
			count += t->ptr_vec[jump + 29].v;
			count += t->ptr_vec[jump + 30].v;
			count += t->ptr_vec[jump + 31].v;			
		}
		i += j;
	}while(alive);

	t->v2 = count;
	t->loops = i;
}

void memory_load_random(thread_data_t *t){
	uint64_t i = 0, j, jump = 1, print = 0, count[32], length = t->memory * 1024 / sizeof(vec_t);
	unsigned bit;
	unsigned int lfsr = 0x80000000;

	for(i = 0; i < 32; i++)
		count[i] = 0;
    
	do{
		for(j = 0; j <= length - 32; j += 32){
			// Linear Feedback Shift Register
			bit  = ~((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 11) ^ (lfsr >> 30) ) & 1;
			lfsr =  (lfsr >> 1) | (bit << 31);

			jump = lfsr % (length - 32);
			count[0] += t->ptr_vec[jump + 0].v;
			count[1] += t->ptr_vec[jump + 1].v;
			count[2] += t->ptr_vec[jump + 2].v;
			count[3] += t->ptr_vec[jump + 3].v;
			count[4] += t->ptr_vec[jump + 4].v;
			count[5] += t->ptr_vec[jump + 5].v;
			count[6] += t->ptr_vec[jump + 6].v;
			count[7] += t->ptr_vec[jump + 7].v;

			count[8] += t->ptr_vec[jump + 8].v;
			count[9] += t->ptr_vec[jump + 9].v;
			count[10] += t->ptr_vec[jump + 10].v;
			count[11] += t->ptr_vec[jump + 11].v;
			count[12] += t->ptr_vec[jump + 12].v;
			count[13] += t->ptr_vec[jump + 13].v;
			count[14] += t->ptr_vec[jump + 14].v;
			count[15] += t->ptr_vec[jump + 15].v;

			count[16] += t->ptr_vec[jump + 16].v;
			count[17] += t->ptr_vec[jump + 17].v;
			count[18] += t->ptr_vec[jump + 18].v;
			count[19] += t->ptr_vec[jump + 19].v;
			count[20] += t->ptr_vec[jump + 20].v;
			count[21] += t->ptr_vec[jump + 21].v;
			count[22] += t->ptr_vec[jump + 22].v;
			count[23] += t->ptr_vec[jump + 23].v;

			count[24] += t->ptr_vec[jump + 24].v;
			count[25] += t->ptr_vec[jump + 25].v;
			count[26] += t->ptr_vec[jump + 26].v;
			count[27] += t->ptr_vec[jump + 27].v;
			count[28] += t->ptr_vec[jump + 28].v;
			count[29] += t->ptr_vec[jump + 29].v;
			count[30] += t->ptr_vec[jump + 30].v;
			count[31] += t->ptr_vec[jump + 31].v;
		}
		i += j;
	}while(alive);

    for(i = 0; i < 8; i++)
        print += count[i];

	t->v2 = print;
	t->loops = i;
}

void memory_store_ind(thread_data_t *t){
	uint64_t i = 0, j, jump = 0, print = 0,length = t->memory * 1024 / sizeof(vec_t);

	do{
		for(j = 0; j <= length - 32; j += 32){
			t->ptr_vec[jump + 0].v = jump;
			t->ptr_vec[jump + 1].v = jump;
			t->ptr_vec[jump + 2].v = jump;
			t->ptr_vec[jump + 3].v = jump;
			t->ptr_vec[jump + 4].v = jump;
			t->ptr_vec[jump + 5].v = jump;
			t->ptr_vec[jump + 6].v = jump;
			t->ptr_vec[jump + 7].v = jump;

			t->ptr_vec[jump + 8].v = jump;
			t->ptr_vec[jump + 9].v = jump;
			t->ptr_vec[jump + 10].v = jump;
			t->ptr_vec[jump + 11].v = jump;
			t->ptr_vec[jump + 12].v = jump;
			t->ptr_vec[jump + 13].v = jump;
			t->ptr_vec[jump + 14].v = jump;
			t->ptr_vec[jump + 15].v = jump;

			t->ptr_vec[jump + 16].v = jump;
			t->ptr_vec[jump + 17].v = jump;
			t->ptr_vec[jump + 18].v = jump;
			t->ptr_vec[jump + 19].v = jump;
			t->ptr_vec[jump + 20].v = jump;
			t->ptr_vec[jump + 21].v = jump;
			t->ptr_vec[jump + 22].v = jump;
			t->ptr_vec[jump + 23].v = jump;

			t->ptr_vec[jump + 24].v = jump;
			t->ptr_vec[jump + 25].v = jump;
			t->ptr_vec[jump + 26].v = jump;
			t->ptr_vec[jump + 27].v = jump;
			t->ptr_vec[jump + 28].v = jump;
			t->ptr_vec[jump + 29].v = jump;
			t->ptr_vec[jump + 30].v = jump;
			t->ptr_vec[jump + 31].v = jump;			
		}
		print += t->ptr_vec[0].v;
		i += j;
	}while(alive);

	t->v2 = print;
	t->loops = i;
}

void memory_store_random(thread_data_t *t){
	uint64_t i = 0, j, jump = 1, print = 0, length = t->memory * 1024 / sizeof(vec_t);
	unsigned bit;
	unsigned int lfsr = 0x80000000;

	do{
		for(j = 0; j <= length - 32; j += 32){
			// Linear Feedback Shift Register
			bit  = ~((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 11) ^ (lfsr >> 30) ) & 1;
			lfsr =  (lfsr >> 1) | (bit << 31);

			jump = lfsr % (length - 32);

			t->ptr_vec[jump + 0].v = jump;
			t->ptr_vec[jump + 1].v = jump;
			t->ptr_vec[jump + 2].v = jump;
			t->ptr_vec[jump + 3].v = jump;
			t->ptr_vec[jump + 4].v = jump;
			t->ptr_vec[jump + 5].v = jump;
			t->ptr_vec[jump + 6].v = jump;
			t->ptr_vec[jump + 7].v = jump;

			t->ptr_vec[jump + 8].v = jump;
			t->ptr_vec[jump + 9].v = jump;
			t->ptr_vec[jump + 10].v = jump;
			t->ptr_vec[jump + 11].v = jump;
			t->ptr_vec[jump + 12].v = jump;
			t->ptr_vec[jump + 13].v = jump;
			t->ptr_vec[jump + 14].v = jump;
			t->ptr_vec[jump + 15].v = jump;

			t->ptr_vec[jump + 16].v = jump;
			t->ptr_vec[jump + 17].v = jump;
			t->ptr_vec[jump + 18].v = jump;
			t->ptr_vec[jump + 19].v = jump;
			t->ptr_vec[jump + 20].v = jump;
			t->ptr_vec[jump + 21].v = jump;
			t->ptr_vec[jump + 22].v = jump;
			t->ptr_vec[jump + 23].v = jump;

			t->ptr_vec[jump + 24].v = jump;
			t->ptr_vec[jump + 25].v = jump;
			t->ptr_vec[jump + 26].v = jump;
			t->ptr_vec[jump + 27].v = jump;
			t->ptr_vec[jump + 28].v = jump;
			t->ptr_vec[jump + 29].v = jump;
			t->ptr_vec[jump + 30].v = jump;
			t->ptr_vec[jump + 31].v = jump;
		}
		print += t->ptr_vec[0].v;
		i += j;
	}while(alive);

	t->v2 = jump;
	t->loops = i;
}

void workload_idle(thread_data_t *t){
	uint64_t i = 0;

	do{
		__asm__ __volatile__ ("pause");
		__asm__ __volatile__ ("pause");
		__asm__ __volatile__ ("pause");
		__asm__ __volatile__ ("pause");
		__asm__ __volatile__ ("pause");
		i++;
	}while(alive);

	t->loops = i;
}