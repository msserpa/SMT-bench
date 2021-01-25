#!/bin/bash

#set -o errexit -o nounset -o pipefail -o posix

declare -a THREADS=("2" "48")
declare -a MAPPING=("hetero" "homo")
declare -a APP_A=("scalar_iadd" "avx128_fma_t" "avx256_fma_t" "avx512_fma_t")
declare -a APP_B=("ctl-complex" "ctl-conditional" "ctl-random" "ctl-small-bbl" "ctl-switch" "dep-chain1" "dep-chain2" "dep-chain3" "dep-chain4" "dep-chain5" "dep-chain6" "fp-add" "fp-div" "fp-mul" "int-add" "int-div" "int-mul" "" "load-dep:32" "load-dep:64" "load-dep:1024" "load-dep:2048" "load-dep:16896" "load-ind:32" "load-ind:64" "load-ind:1024" "load-ind:2048" "load-ind:16896" "load-rand:32" "load-rand:64" "load-rand:1024" "load-rand:2048" "load-rand:16896" "store-ind:32" "store-ind:64" "store-ind:1024" "store-ind:2048" "store-ind:16896" "store-rand:32" "store-rand:64" "store-rand:1024" "store-rand:2048" "store-rand:16896" "idle" "ucomis_clean" "ucomis_dirty" "scalar_iadd" "avx128_iadd" "avx256_iadd" "avx512_iadd" "avx128_iadd16" "avx256_iadd16" "avx512_iadd16" "avx128_iadd_t" "avx256_iadd_t" "avx128_mov_sparse" "avx256_mov_sparse" "avx512_mov_sparse" "avx128_merge_sparse" "avx256_merge_sparse" "avx512_merge_sparse" "avx128_vshift" "avx256_vshift" "avx512_vshift" "avx128_vshift_t" "avx256_vshift_t" "avx512_vshift_t" "avx128_vlzcnt" "avx256_vlzcnt" "avx512_vlzcnt" "avx128_vlzcnt_t" "avx256_vlzcnt_t" "avx512_vlzcnt_t" "avx128_imul" "avx256_imul" "avx512_imul" "avx128_fma_sparse" "avx256_fma_sparse" "avx512_fma_sparse" "avx128_fma" "avx256_fma" "avx512_fma" "avx128_fma_t" "avx256_fma_t" "avx512_fma_t" "avx512_vpermw" "avx512_vpermw_t" "avx512_vpermd" "avx512_vpermd_t")

mkdir -p ./DoE/

OUTPUT=./DoE/`hostname | awk -F. {'print $1'}`.csv
rm -f $OUTPUT

size=0
for th in "${THREADS[@]}"; do
	for map in "${MAPPING[@]}"; do
		for i in ${!APP_A[*]}; do
			appA=${APP_A[$i]}
			for j in ${!APP_B[*]}; do
				appB=${APP_B[$j]}
		        
		        if [ "$appA" != "$appB" ]; then
					if [ $# -eq 1 ] && [ "$1" == "papi" ]; then
						declare -a PAPI=(`printf '%s\n' $(papi_avail |grep Yes | awk {'print $1'} | shuf | shuf) | sed s'/,\+$//' | tr '\n' ' '`)
						for event in "${PAPI[@]}"; do
							echo "$th;$event;$map;$appA;$appB" >> $OUTPUT
							size=$((size+1))
						done
					else
						echo "$th;$map;$appA;$appB" >> $OUTPUT
						size=$((size+1))
					fi
				fi
			done
		done
	done
done
printf "\tcreating full factorial with $size runs ...\n"

for i in `seq 1 10`; do
	shuf $OUTPUT -o $OUTPUT
done
