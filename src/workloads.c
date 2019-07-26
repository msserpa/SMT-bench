#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/mixed.h"
#include "../include/workloads.h"

extern thread_data_t *threads;
extern uint32_t nt;
uint64_t **iterations;

void init_class(){
	printf("init_class\n");
	iterations[CONTROL_COMPLEX][0] = 3545750420/20;
	iterations[CONTROL_CONDITIONAL][0] = 3559666634/20;
	iterations[CONTROL_RANDOM][0] = 166313500/20;
	iterations[CONTROL_SMALL_BBL][0] = 4312068293/20;
	iterations[CONTROL_SWITCH][0] = 4145062272/20;
	iterations[DEPENDENCY_CHAIN1][0] = 134491917/20;
	iterations[DEPENDENCY_CHAIN2][0] = 269507186/20;
	iterations[DEPENDENCY_CHAIN3][0] = 420045244/20;
	iterations[DEPENDENCY_CHAIN4][0] = 534170738/20;
	iterations[DEPENDENCY_CHAIN5][0] = 620024682/20;
	iterations[DEPENDENCY_CHAIN6][0] = 701546406/20;
	iterations[EXECUTION_FP_ADD_IND][0] = 808655722/20;
	iterations[EXECUTION_FP_DIV_IND][0] = 100786069/20;
	iterations[EXECUTION_FP_MUL_IND][0] = 1293847285/20;
	iterations[EXECUTION_INT_ADD_IND][0] = 708815868/20;
	iterations[EXECUTION_INT_DIV_IND][0] = 20738284/20;
	iterations[EXECUTION_INT_MUL_IND][0] = 749736007/20;
	iterations[MEMORY_LOAD_DEP][0] = 2791178822/20; //16KB
	iterations[MEMORY_LOAD_DEP][1] = 2520048062/20; //32KB
	iterations[MEMORY_LOAD_DEP][2] = 1318790137/20; //64KB
	iterations[MEMORY_LOAD_DEP][3] = 0; //128KB
	iterations[MEMORY_LOAD_DEP][4] = 0; //256KB
	iterations[MEMORY_LOAD_DEP][5] = 0; //512KB
	iterations[MEMORY_LOAD_DEP][6] = 0; //1024KB
	iterations[MEMORY_LOAD_DEP][7] = 0; //2048KB
	iterations[MEMORY_LOAD_DEP][8] = 0; //4096KB
	iterations[MEMORY_LOAD_DEP][9] = 280192409/20; //8192KB
	iterations[MEMORY_LOAD_DEP][10] = 0; //16384KB
	iterations[MEMORY_LOAD_DEP][11] = 0; //32768KB
	iterations[MEMORY_LOAD_DEP][12] = 0; //65536KB
	iterations[MEMORY_LOAD_IND][0] = 3594545828/20; //16KB
	iterations[MEMORY_LOAD_IND][1] = 3589516492/20; //32KB
	iterations[MEMORY_LOAD_IND][2] = 3586875394/20; //64KB
	iterations[MEMORY_LOAD_IND][3] = 0; //128KB
	iterations[MEMORY_LOAD_IND][4] = 0; //256KB
	iterations[MEMORY_LOAD_IND][5] = 0; //512KB
	iterations[MEMORY_LOAD_IND][6] = 0; //1024KB
	iterations[MEMORY_LOAD_IND][7] = 0; //2048KB
	iterations[MEMORY_LOAD_IND][8] = 0; //4096KB
	iterations[MEMORY_LOAD_IND][9] = 3560960462/20; //8192KB
	iterations[MEMORY_LOAD_IND][10] = 0; //16384KB
	iterations[MEMORY_LOAD_IND][11] = 0; //32768KB
	iterations[MEMORY_LOAD_IND][12] = 0; //65536KB
	iterations[MEMORY_LOAD_RANDOM][0] = 5885559983/20; //16KB
	iterations[MEMORY_LOAD_RANDOM][1] = 5848185979/20; //32KB
	iterations[MEMORY_LOAD_RANDOM][2] = 5423904255/20; //64KB
	iterations[MEMORY_LOAD_RANDOM][3] = 0; //128KB
	iterations[MEMORY_LOAD_RANDOM][4] = 0; //256KB
	iterations[MEMORY_LOAD_RANDOM][5] = 0; //512KB
	iterations[MEMORY_LOAD_RANDOM][6] = 0; //1024KB
	iterations[MEMORY_LOAD_RANDOM][7] = 0; //2048KB
	iterations[MEMORY_LOAD_RANDOM][8] = 0; //4096KB
	iterations[MEMORY_LOAD_RANDOM][9] = 559947559/20; //8192KB
	iterations[MEMORY_LOAD_RANDOM][10] = 0; //16384KB
	iterations[MEMORY_LOAD_RANDOM][11] = 0; //32768KB
	iterations[MEMORY_LOAD_RANDOM][12] = 0; //65536KB
	iterations[MEMORY_STORE_IND][0] = 0; //16KB
	iterations[MEMORY_STORE_IND][1] = 0; //32KB
	iterations[MEMORY_STORE_IND][2] = 0; //64KB
	iterations[MEMORY_STORE_IND][3] = 0; //128KB
	iterations[MEMORY_STORE_IND][4] = 0; //256KB
	iterations[MEMORY_STORE_IND][5] = 0; //512KB
	iterations[MEMORY_STORE_IND][6] = 0; //1024KB
	iterations[MEMORY_STORE_IND][7] = 0; //2048KB
	iterations[MEMORY_STORE_IND][8] = 0; //4096KB
	iterations[MEMORY_STORE_IND][9] = 0; //8192KB
	iterations[MEMORY_STORE_IND][10] = 0; //16384KB
	iterations[MEMORY_STORE_IND][11] = 0; //32768KB
	iterations[MEMORY_STORE_IND][12] = 0; //65536KB
	iterations[MEMORY_STORE_RANDOM][0] = 0; //16KB
	iterations[MEMORY_STORE_RANDOM][1] = 0; //32KB
	iterations[MEMORY_STORE_RANDOM][2] = 0; //64KB
	iterations[MEMORY_STORE_RANDOM][3] = 0; //128KB
	iterations[MEMORY_STORE_RANDOM][4] = 0; //256KB
	iterations[MEMORY_STORE_RANDOM][5] = 0; //512KB
	iterations[MEMORY_STORE_RANDOM][6] = 0; //1024KB
	iterations[MEMORY_STORE_RANDOM][7] = 0; //2048KB
	iterations[MEMORY_STORE_RANDOM][8] = 0; //4096KB
	iterations[MEMORY_STORE_RANDOM][9] = 0; //8192KB
	iterations[MEMORY_STORE_RANDOM][10] = 0; //16384KB
	iterations[MEMORY_STORE_RANDOM][11] = 0; //32768KB
	iterations[MEMORY_STORE_RANDOM][12] = 0; //65536KB
	iterations[WORKLOAD_IDLE][0] = 0;
}

void init_class_A(){
	printf("init_class_A\n");
	iterations[CONTROL_COMPLEX][0] = 945899543;
	iterations[CONTROL_CONDITIONAL][0] = 956757940;
	iterations[CONTROL_RANDOM][0] = 57766744;
	iterations[CONTROL_SMALL_BBL][0] = 1500044190;
	iterations[CONTROL_SWITCH][0] = 982680794;
	iterations[DEPENDENCY_CHAIN1][0] = 40621531;
	iterations[DEPENDENCY_CHAIN2][0] = 70495570;
	iterations[DEPENDENCY_CHAIN3][0] = 95813971;
	iterations[DEPENDENCY_CHAIN4][0] = 104432313;
	iterations[DEPENDENCY_CHAIN5][0] = 120954956;
	iterations[DEPENDENCY_CHAIN6][0] = 129820576;
	iterations[EXECUTION_FP_ADD_IND][0] = 178139683;
	iterations[EXECUTION_FP_DIV_IND][0] = 42946779;
	iterations[EXECUTION_FP_MUL_IND][0] = 351145519;
	iterations[EXECUTION_INT_ADD_IND][0] = 132109878;
	iterations[EXECUTION_INT_DIV_IND][0] = 8169954;
	iterations[EXECUTION_INT_MUL_IND][0] = 126296006;
	iterations[MEMORY_LOAD_DEP][0] = 997911488; //16KB
	iterations[MEMORY_LOAD_DEP][1] = 547818475; //32KB
	iterations[MEMORY_LOAD_DEP][2] = 528737621; //64KB
	iterations[MEMORY_LOAD_DEP][3] = 554840149; //128KB
	iterations[MEMORY_LOAD_DEP][4] = 512502101; //256KB
	iterations[MEMORY_LOAD_DEP][5] = 511714987; //512KB
	iterations[MEMORY_LOAD_DEP][6] = 472745984; //1024KB
	iterations[MEMORY_LOAD_DEP][7] = 462303232; //2048KB
	iterations[MEMORY_LOAD_DEP][8] = 129982464; //4096KB
	iterations[MEMORY_LOAD_DEP][9] = 55929515; //8192KB
	iterations[MEMORY_LOAD_DEP][10] = 68190208; //16384KB
	iterations[MEMORY_LOAD_DEP][11] = 77463552; //32768KB
	iterations[MEMORY_LOAD_DEP][12] = 93192192; //65536KB
	iterations[MEMORY_LOAD_IND][0] = 1294112523; //16KB
	iterations[MEMORY_LOAD_IND][1] = 1296502379; //32KB
	iterations[MEMORY_LOAD_IND][2] = 1298342272; //64KB
	iterations[MEMORY_LOAD_IND][3] = 1300037461; //128KB
	iterations[MEMORY_LOAD_IND][4] = 1278506667; //256KB
	iterations[MEMORY_LOAD_IND][5] = 1299353600; //512KB
	iterations[MEMORY_LOAD_IND][6] = 1299585024; //1024KB
	iterations[MEMORY_LOAD_IND][7] = 1299437382; //2048KB
	iterations[MEMORY_LOAD_IND][8] = 1298819258; //4096KB
	iterations[MEMORY_LOAD_IND][9] = 1300365312; //8192KB
	iterations[MEMORY_LOAD_IND][10] = 1300341481; //16384KB
	iterations[MEMORY_LOAD_IND][11] = 1296707212; //32768KB
	iterations[MEMORY_LOAD_IND][12] = 1299900602; //65536KB
	iterations[MEMORY_LOAD_RANDOM][0] = 1572710249; //16KB
	iterations[MEMORY_LOAD_RANDOM][1] = 1437454499; //32KB
	iterations[MEMORY_LOAD_RANDOM][2] = 1360599366; //64KB
	iterations[MEMORY_LOAD_RANDOM][3] = 1240797184; //128KB
	iterations[MEMORY_LOAD_RANDOM][4] = 999773836; //256KB
	iterations[MEMORY_LOAD_RANDOM][5] = 851009536; //512KB
	iterations[MEMORY_LOAD_RANDOM][6] = 741906991; //1024KB
	iterations[MEMORY_LOAD_RANDOM][7] = 159157155; //2048KB
	iterations[MEMORY_LOAD_RANDOM][8] = 69235805; //4096KB
	iterations[MEMORY_LOAD_RANDOM][9] = 65684945; //8192KB
	iterations[MEMORY_LOAD_RANDOM][10] = 76557964; //16384KB
	iterations[MEMORY_LOAD_RANDOM][11] = 85053812; //32768KB
	iterations[MEMORY_LOAD_RANDOM][12] = 104762275; //65536KB
	iterations[MEMORY_STORE_IND][0] = 2489355148; //16KB
	iterations[MEMORY_STORE_IND][1] = 2518942580; //32KB
	iterations[MEMORY_STORE_IND][2] = 2522597981; //64KB
	iterations[MEMORY_STORE_IND][3] = 2522503913; //128KB
	iterations[MEMORY_STORE_IND][4] = 2520692550; //256KB
	iterations[MEMORY_STORE_IND][5] = 2508260073; //512KB
	iterations[MEMORY_STORE_IND][6] = 2504721873; //1024KB
	iterations[MEMORY_STORE_IND][7] = 2492310249; //2048KB
	iterations[MEMORY_STORE_IND][8] = 2487058432; //4096KB
	iterations[MEMORY_STORE_IND][9] = 2494729123; //8192KB
	iterations[MEMORY_STORE_IND][10] = 2493192006; //16384KB
	iterations[MEMORY_STORE_IND][11] = 2493656716; //32768KB
	iterations[MEMORY_STORE_IND][12] = 2496707119; //65536KB
	iterations[MEMORY_STORE_RANDOM][0] = 1812209699; //16KB
	iterations[MEMORY_STORE_RANDOM][1] = 1517841222; //32KB
	iterations[MEMORY_STORE_RANDOM][2] = 1132062953; //64KB
	iterations[MEMORY_STORE_RANDOM][3] = 947413364; //128KB
	iterations[MEMORY_STORE_RANDOM][4] = 770901830; //256KB
	iterations[MEMORY_STORE_RANDOM][5] = 676311040; //512KB
	iterations[MEMORY_STORE_RANDOM][6] = 608290257; //1024KB
	iterations[MEMORY_STORE_RANDOM][7] = 76067933; //2048KB
	iterations[MEMORY_STORE_RANDOM][8] = 43810816; //4096KB
	iterations[MEMORY_STORE_RANDOM][9] = 40584657; //8192KB
	iterations[MEMORY_STORE_RANDOM][10] = 47674461; //16384KB
	iterations[MEMORY_STORE_RANDOM][11] = 55550697; //32768KB
	iterations[MEMORY_STORE_RANDOM][12] = 62294947; //65536KB
	iterations[WORKLOAD_IDLE][0] = 0;
}

void init_class_B(){
	printf("init_class_B\n");
	iterations[CONTROL_COMPLEX][0] = 3545750420;
	iterations[CONTROL_CONDITIONAL][0] = 3559666634;
	iterations[CONTROL_RANDOM][0] = 166313500;
	iterations[CONTROL_SMALL_BBL][0] = 4312068293;
	iterations[CONTROL_SWITCH][0] = 4145062272;
	iterations[DEPENDENCY_CHAIN1][0] = 134491917;
	iterations[DEPENDENCY_CHAIN2][0] = 269507186;
	iterations[DEPENDENCY_CHAIN3][0] = 420045244;
	iterations[DEPENDENCY_CHAIN4][0] = 534170738;
	iterations[DEPENDENCY_CHAIN5][0] = 620024682;
	iterations[DEPENDENCY_CHAIN6][0] = 701546406;
	iterations[EXECUTION_FP_ADD_IND][0] = 808655722;
	iterations[EXECUTION_FP_DIV_IND][0] = 100786069;
	iterations[EXECUTION_FP_MUL_IND][0] = 1293847285;
	iterations[EXECUTION_INT_ADD_IND][0] = 708815868;
	iterations[EXECUTION_INT_DIV_IND][0] = 20738284;
	iterations[EXECUTION_INT_MUL_IND][0] = 749736007;
	iterations[MEMORY_LOAD_DEP][0] = 2791178822; //16KB
	iterations[MEMORY_LOAD_DEP][1] = 2520048062; //32KB
	iterations[MEMORY_LOAD_DEP][2] = 1318790137; //64KB
	iterations[MEMORY_LOAD_DEP][3] = 0; //128KB
	iterations[MEMORY_LOAD_DEP][4] = 0; //256KB
	iterations[MEMORY_LOAD_DEP][5] = 0; //512KB
	iterations[MEMORY_LOAD_DEP][6] = 0; //1024KB
	iterations[MEMORY_LOAD_DEP][7] = 0; //2048KB
	iterations[MEMORY_LOAD_DEP][8] = 0; //4096KB
	iterations[MEMORY_LOAD_DEP][9] = 280192409; //8192KB
	iterations[MEMORY_LOAD_DEP][10] = 0; //16384KB
	iterations[MEMORY_LOAD_DEP][11] = 0; //32768KB
	iterations[MEMORY_LOAD_DEP][12] = 0; //65536KB
	iterations[MEMORY_LOAD_IND][0] = 3594545828; //16KB
	iterations[MEMORY_LOAD_IND][1] = 3589516492; //32KB
	iterations[MEMORY_LOAD_IND][2] = 3586875394; //64KB
	iterations[MEMORY_LOAD_IND][3] = 0; //128KB
	iterations[MEMORY_LOAD_IND][4] = 0; //256KB
	iterations[MEMORY_LOAD_IND][5] = 0; //512KB
	iterations[MEMORY_LOAD_IND][6] = 0; //1024KB
	iterations[MEMORY_LOAD_IND][7] = 0; //2048KB
	iterations[MEMORY_LOAD_IND][8] = 0; //4096KB
	iterations[MEMORY_LOAD_IND][9] = 3560960462; //8192KB
	iterations[MEMORY_LOAD_IND][10] = 0; //16384KB
	iterations[MEMORY_LOAD_IND][11] = 0; //32768KB
	iterations[MEMORY_LOAD_IND][12] = 0; //65536KB
	iterations[MEMORY_LOAD_RANDOM][0] = 5885559983; //16KB
	iterations[MEMORY_LOAD_RANDOM][1] = 5848185979; //32KB
	iterations[MEMORY_LOAD_RANDOM][2] = 5423904255; //64KB
	iterations[MEMORY_LOAD_RANDOM][3] = 0; //128KB
	iterations[MEMORY_LOAD_RANDOM][4] = 0; //256KB
	iterations[MEMORY_LOAD_RANDOM][5] = 0; //512KB
	iterations[MEMORY_LOAD_RANDOM][6] = 0; //1024KB
	iterations[MEMORY_LOAD_RANDOM][7] = 0; //2048KB
	iterations[MEMORY_LOAD_RANDOM][8] = 0; //4096KB
	iterations[MEMORY_LOAD_RANDOM][9] = 559947559; //8192KB
	iterations[MEMORY_LOAD_RANDOM][10] = 0; //16384KB
	iterations[MEMORY_LOAD_RANDOM][11] = 0; //32768KB
	iterations[MEMORY_LOAD_RANDOM][12] = 0; //65536KB
	iterations[MEMORY_STORE_IND][0] = 0; //16KB
	iterations[MEMORY_STORE_IND][1] = 0; //32KB
	iterations[MEMORY_STORE_IND][2] = 0; //64KB
	iterations[MEMORY_STORE_IND][3] = 0; //128KB
	iterations[MEMORY_STORE_IND][4] = 0; //256KB
	iterations[MEMORY_STORE_IND][5] = 0; //512KB
	iterations[MEMORY_STORE_IND][6] = 0; //1024KB
	iterations[MEMORY_STORE_IND][7] = 0; //2048KB
	iterations[MEMORY_STORE_IND][8] = 0; //4096KB
	iterations[MEMORY_STORE_IND][9] = 0; //8192KB
	iterations[MEMORY_STORE_IND][10] = 0; //16384KB
	iterations[MEMORY_STORE_IND][11] = 0; //32768KB
	iterations[MEMORY_STORE_IND][12] = 0; //65536KB
	iterations[MEMORY_STORE_RANDOM][0] = 0; //16KB
	iterations[MEMORY_STORE_RANDOM][1] = 0; //32KB
	iterations[MEMORY_STORE_RANDOM][2] = 0; //64KB
	iterations[MEMORY_STORE_RANDOM][3] = 0; //128KB
	iterations[MEMORY_STORE_RANDOM][4] = 0; //256KB
	iterations[MEMORY_STORE_RANDOM][5] = 0; //512KB
	iterations[MEMORY_STORE_RANDOM][6] = 0; //1024KB
	iterations[MEMORY_STORE_RANDOM][7] = 0; //2048KB
	iterations[MEMORY_STORE_RANDOM][8] = 0; //4096KB
	iterations[MEMORY_STORE_RANDOM][9] = 0; //8192KB
	iterations[MEMORY_STORE_RANDOM][10] = 0; //16384KB
	iterations[MEMORY_STORE_RANDOM][11] = 0; //32768KB
	iterations[MEMORY_STORE_RANDOM][12] = 0; //65536KB
	iterations[WORKLOAD_IDLE][0] = 0;
}

void init_class_C(){
	printf("init_class_C\n");
	iterations[CONTROL_COMPLEX][0] = 11429171010;
	iterations[CONTROL_CONDITIONAL][0] = 11450281175;
	iterations[CONTROL_RANDOM][0] = 691820796;
	iterations[CONTROL_SMALL_BBL][0] = 18181335730;
	iterations[CONTROL_SWITCH][0] = 11798603206;
	iterations[DEPENDENCY_CHAIN1][0] = 486551269;
	iterations[DEPENDENCY_CHAIN2][0] = 831921433;
	iterations[DEPENDENCY_CHAIN3][0] = 1151930167;
	iterations[DEPENDENCY_CHAIN4][0] = 1273947776;
	iterations[DEPENDENCY_CHAIN5][0] = 1468295836;
	iterations[DEPENDENCY_CHAIN6][0] = 1562504802;
	iterations[EXECUTION_FP_ADD_IND][0] = 2108226007;
	iterations[EXECUTION_FP_DIV_IND][0] = 511461171;
	iterations[EXECUTION_FP_MUL_IND][0] = 4293107171;
	iterations[EXECUTION_INT_ADD_IND][0] = 1585778047;
	iterations[EXECUTION_INT_DIV_IND][0] = 98139806;
	iterations[EXECUTION_INT_MUL_IND][0] = 1511582954;
	iterations[MEMORY_LOAD_DEP][0] = 11976905996; //16KB
	iterations[MEMORY_LOAD_DEP][1] = 6670170531; //32KB
	iterations[MEMORY_LOAD_DEP][2] = 6450912396; //64KB
	iterations[MEMORY_LOAD_DEP][3] = 6412599668; //128KB
	iterations[MEMORY_LOAD_DEP][4] = 6135612137; //256KB
	iterations[MEMORY_LOAD_DEP][5] = 6152439622; //512KB
	iterations[MEMORY_LOAD_DEP][6] = 5925756928; //1024KB
	iterations[MEMORY_LOAD_DEP][7] = 3193135849; //2048KB
	iterations[MEMORY_LOAD_DEP][8] = 585453940; //4096KB
	iterations[MEMORY_LOAD_DEP][9] = 680716474; //8192KB
	iterations[MEMORY_LOAD_DEP][10] = 827409873; //16384KB
	iterations[MEMORY_LOAD_DEP][11] = 931397632; //32768KB
	iterations[MEMORY_LOAD_DEP][12] = 1118496954; //65536KB
	iterations[MEMORY_LOAD_IND][0] = 15531475503; //16KB
	iterations[MEMORY_LOAD_IND][1] = 15553604608; //32KB
	iterations[MEMORY_LOAD_IND][2] = 15566087215; //64KB
	iterations[MEMORY_LOAD_IND][3] = 15579073350; //128KB
	iterations[MEMORY_LOAD_IND][4] = 15309793466; //256KB
	iterations[MEMORY_LOAD_IND][5] = 15567935302; //512KB
	iterations[MEMORY_LOAD_IND][6] = 15584843590; //1024KB
	iterations[MEMORY_LOAD_IND][7] = 15584261213; //2048KB
	iterations[MEMORY_LOAD_IND][8] = 15588440623; //4096KB
	iterations[MEMORY_LOAD_IND][9] = 15586724771; //8192KB
	iterations[MEMORY_LOAD_IND][10] = 15594040972; //16384KB
	iterations[MEMORY_LOAD_IND][11] = 15589084067; //32768KB
	iterations[MEMORY_LOAD_IND][12] = 15593278371; //65536KB
	iterations[MEMORY_LOAD_RANDOM][0] = 18904209210; //16KB
	iterations[MEMORY_LOAD_RANDOM][1] = 17259223343; //32KB
	iterations[MEMORY_LOAD_RANDOM][2] = 16380481536; //64KB
	iterations[MEMORY_LOAD_RANDOM][3] = 15081157073; //128KB
	iterations[MEMORY_LOAD_RANDOM][4] = 11997600303; //256KB
	iterations[MEMORY_LOAD_RANDOM][5] = 10114395788; //512KB
	iterations[MEMORY_LOAD_RANDOM][6] = 8658841228; //1024KB
	iterations[MEMORY_LOAD_RANDOM][7] = 2705993356; //2048KB
	iterations[MEMORY_LOAD_RANDOM][8] = 862549085; //4096KB
	iterations[MEMORY_LOAD_RANDOM][9] = 814403956; //8192KB
	iterations[MEMORY_LOAD_RANDOM][10] = 919601152; //16384KB
	iterations[MEMORY_LOAD_RANDOM][11] = 1025840966; //32768KB
	iterations[MEMORY_LOAD_RANDOM][12] = 1252667020; //65536KB
	iterations[MEMORY_STORE_IND][0] = 29848532224; //16KB
	iterations[MEMORY_STORE_IND][1] = 30107401937; //32KB
	iterations[MEMORY_STORE_IND][2] = 30202487063; //64KB
	iterations[MEMORY_STORE_IND][3] = 30252897652; //128KB
	iterations[MEMORY_STORE_IND][4] = 30301594717; //256KB
	iterations[MEMORY_STORE_IND][5] = 30004652218; //512KB
	iterations[MEMORY_STORE_IND][6] = 30134932573; //1024KB
	iterations[MEMORY_STORE_IND][7] = 30029916346; //2048KB
	iterations[MEMORY_STORE_IND][8] = 29971629521; //4096KB
	iterations[MEMORY_STORE_IND][9] = 30026039296; //8192KB
	iterations[MEMORY_STORE_IND][10] = 29914669801; //16384KB
	iterations[MEMORY_STORE_IND][11] = 29935224273; //32768KB
	iterations[MEMORY_STORE_IND][12] = 29766498863; //65536KB
	iterations[MEMORY_STORE_RANDOM][0] = 21746188812; //16KB
	iterations[MEMORY_STORE_RANDOM][1] = 18127075491; //32KB
	iterations[MEMORY_STORE_RANDOM][2] = 13624963025; //64KB
	iterations[MEMORY_STORE_RANDOM][3] = 11444278458; //128KB
	iterations[MEMORY_STORE_RANDOM][4] = 9263666641; //256KB
	iterations[MEMORY_STORE_RANDOM][5] = 8128599133; //512KB
	iterations[MEMORY_STORE_RANDOM][6] = 7295759453; //1024KB
	iterations[MEMORY_STORE_RANDOM][7] = 908588125; //2048KB
	iterations[MEMORY_STORE_RANDOM][8] = 526939229; //4096KB
	iterations[MEMORY_STORE_RANDOM][9] = 511973190; //8192KB
	iterations[MEMORY_STORE_RANDOM][10] = 571497751; //16384KB
	iterations[MEMORY_STORE_RANDOM][11] = 628668975; //32768KB
	iterations[MEMORY_STORE_RANDOM][12] = 748254301; //65536KB
	iterations[WORKLOAD_IDLE][0] = 0;
}

void set_workload_iterations(char class){
	uint64_t i;
	iterations = (uint64_t **) (malloc(NWORKLOADS * sizeof(uint64_t *)));
	for(i = 0; i < NWORKLOADS; i++){
		if(i < 17)
			iterations[i] = (uint64_t *) (calloc(1,     sizeof(uint64_t)));
		else
			iterations[i] = (uint64_t *) (calloc(13, sizeof(uint64_t)));
	}
			
	if(class == 'A')
		init_class_A();
	else if(class == 'B')
		init_class_B();
	else if(class == 'C')
		init_class_C();
	else
		init_class();

	for(i = 0; i < nt; i++){
		if(threads[i].memoryA <= (unsigned long int) powf(2, 12 + 4)){
			if(threads[i].memoryA == 0)
				threads[i].iterations = iterations[threads[i].typeA][0];
			else
				threads[i].iterations = iterations[threads[i].typeA][(int) log2f(threads[i].memoryA) - 4];
		}
		  else
		  	threads[i].iterations = iterations[threads[i].typeA][12];
	}

	for(i = 0; i < NWORKLOADS; i++)
		free(iterations[i]);
	free(iterations);
}

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
	printf("control_complex\n");
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
	}while(i < t->iterations);

	t->v2 = k;
}

void control_conditional(thread_data_t *t){
	printf("control_conditional\n");
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
	}while(i < t->iterations);

	t->v2 = print;
}

void control_random(thread_data_t *t){
	printf("control_random\n");
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
	}while(i < t->iterations);

	t->v2 = bit;
}

void control_small_bbl(thread_data_t *t){
	printf("control_small_bbl\n");
	uint64_t i = 0, j, print = 0, count[64];
   
   	for(j = 0; j < 64; j++)
        count[j] = 0;

	do{
		i++;
	}while(i < t->iterations);
	
	for(j = 0; j < 64; j++)
		print += count[j];

	t->v2 = print;
}

void control_switch(thread_data_t *t){
	printf("control_switch\n");
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
	}while(i < t->iterations);

	t->v2 = print;
}

void dependency_chain1(thread_data_t *t){
	printf("dependency_chain1\n");
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
	}while(i < t->iterations);

	t->v2 = count0;
}

void dependency_chain2(thread_data_t *t){
	printf("dependency_chain2\n");
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
	}while(i < t->iterations);

	t->v2 = count1;
}


void dependency_chain3(thread_data_t *t){
	printf("dependency_chain3\n");
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
	}while(i < t->iterations);

	t->v2 = count2;
}

void dependency_chain4(thread_data_t *t){
	printf("dependency_chain4\n");
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
	}while(i < t->iterations);

	t->v2 = count3;
}

void dependency_chain5(thread_data_t *t){
	printf("dependency_chain5\n");
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
	}while(i < t->iterations);

	t->v2 = count4;
}

void dependency_chain6(thread_data_t *t){
	printf("dependency_chain6\n");
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
	}while(i < t->iterations);

	t->v2 = count5;
}

void execution_fp_add_ind(thread_data_t *t){
	printf("execution_fp_add_ind\n");
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
	}while(i < t->iterations);

    asm volatile("push $0x0":::);
    asm volatile("movsd %%xmm0, (%%rsp)" : : : );
    asm volatile("mov (%%rsp), %0" : "=r"(count) : : );
    asm volatile("pop %%rbx" : : : "rbx");	

	t->v2 = count;
}

void execution_fp_div_ind(thread_data_t *t){
	printf("execution_fp_div_ind\n");
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
	}while(i < t->iterations);

    asm volatile("push $0x0":::);
    asm volatile("movsd %%xmm0, (%%rsp)" : : : );
    asm volatile("mov (%%rsp), %0" : "=r"(count) : : );
    asm volatile("pop %%rbx" : : : "rbx");

	t->v2 = count;
}

void execution_fp_mul_ind(thread_data_t *t){
	printf("execution_fp_mul_ind\n");
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
	}while(i < t->iterations);

    asm volatile("push $0x0":::);
    asm volatile("movsd %%xmm0, (%%rsp)" : : : );
    asm volatile("mov (%%rsp), %0" : "=r"(count) : : );
    asm volatile("pop %%rbx" : : : "rbx");

	t->v2 = count;
}

void execution_int_add_ind(thread_data_t *t){
	printf("execution_int_add_ind\n");
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
	}while(i < t->iterations);

	t->v2 = count7;
}

void execution_int_div_ind(thread_data_t *t){
	printf("execution_int_div_ind\n");
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
	}while(i < t->iterations);
	asm volatile("mov %%rbx, %0" : "=r"(count) : : "rbx");

	t->v2 = count;
}

void execution_int_mul_ind(thread_data_t *t){
	printf("execution_int_mul_ind\n");
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
	}while(i < t->iterations);

	t->v2 = count7;
}

void alloc_list(thread_data_t *t){

	uint64_t i, length = t->memoryA * 1024 / sizeof(list_t);
	list_t *ptr_this;

	if(length == 0 || length % 32 != 0){
		fprintf(stderr, "The array size (%lu) needs to be divisible by 32.\n", length);
		exit(EXIT_FAILURE);
	}

	assert(posix_memalign((void **) &t->ptr_list, CACHE_LINE_SIZE, length * sizeof(list_t)) == 0);
	assert(t->ptr_list != NULL);

    ptr_this = t->ptr_list;
	for(i = 0; i < length - 1; i++){
		ptr_this->v = 1;
		ptr_this->next = &t->ptr_list[i+1];
		ptr_this = ptr_this->next;
		ptr_this->next = NULL;
	}
	ptr_this->v = 1;
	ptr_this->next = &t->ptr_list[0];
}

void free_list(thread_data_t *t){
	free(t->ptr_list);
}

void memory_load_dep(thread_data_t *t){
	printf("memory_load_dep\n");
	uint64_t i = 0, j = 0, print = 0, length = t->memoryA * 1024 / sizeof(list_t);
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
	}while(i < t->iterations);

	t->v2 = print;
}

void alloc_vec(thread_data_t *t){

	uint64_t i, length = t->memoryA * 1024 / sizeof(vec_t);

	if(length == 0 || length % 32 != 0){
		fprintf(stderr, "The array size (%lu) needs to be divisible by 32.\n", length);
		exit(EXIT_FAILURE);
	}

	assert(posix_memalign((void **) &t->ptr_vec, CACHE_LINE_SIZE, length * sizeof(vec_t)) == 0);
	assert(t->ptr_vec != NULL);

	for(i = 0; i < length; i++)
        t->ptr_vec[i].v = 1;
}

void free_vec(thread_data_t *t){
	free(t->ptr_vec);
}

void init_vec(thread_data_t *t){
	uint64_t i, length = t->memoryA * 1024 / sizeof(vec_t);
	
	for(i = 0; i < length; i++)
		t->ptr_vec[i].v = i;
}

void memory_load_ind(thread_data_t *t){
	printf("memory_load_ind\n");
	uint64_t i = 0, j, jump = 0, count = 0, length = t->memoryA * 1024 / sizeof(vec_t);

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
	}while(i < t->iterations);

	t->v2 = count;
}

void memory_load_random(thread_data_t *t){
	printf("memory_load_random\n");
	uint64_t i = 0, j, jump = 1, print = 0, count[32], length = t->memoryA * 1024 / sizeof(vec_t);
	unsigned bit;
	unsigned int lfsr = 0x80000000;

	for(j = 0; j < 32; j++)
		count[j] = 0;
    
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
	}while(i < t->iterations);

	for(j = 0; j < 8; j++)
		print += count[j];

	t->v2 = print;
}

void memory_store_ind(thread_data_t *t){
	printf("memory_store_ind\n");
	uint64_t i = 0, j, jump = 0, print = 0,length = t->memoryA * 1024 / sizeof(vec_t);

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
	}while(i < t->iterations);

	t->v2 = print;
}

void memory_store_random(thread_data_t *t){
	printf("memory_store_random\n");
	uint64_t i = 0, j, jump = 1, print = 0, length = t->memoryA * 1024 / sizeof(vec_t);
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
	}while(i < t->iterations);

	t->v2 = jump;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void workload_idle(thread_data_t *t){
	printf("workload_idle\n");
	__asm__ __volatile__ ("pause");
}
#pragma GCC diagnostic pop
