#!/bin/bash

set -o errexit -o nounset -o pipefail -o posix

declare -a MAPPING=("os" "homo" "hetero")
declare -a APP=("ctl-complex" "ctl-conditional" "ctl-random" "ctl-small-bbl" "ctl-switch" "dep-chain1" "dep-chain2" "dep-chain3" "dep-chain4" "dep-chain5" "dep-chain6" "fp-add" "fp-div" "fp-mul" "int-add" "int-div" "int-mul" "load-dep:32" "load-ind:32" "load-rand:32" "idle"),

OUTPUT=./DoE/`hostname`.csv
rm -f $OUTPUT

size=0
for map in "${MAPPING[@]}"; do
	for i in ${!APP[*]}; do
		appA=${APP[$i]}
		for j in ${!APP[*]}; do
			appB=${APP[$j]}
			if (( i < j )); then
				echo "$map,$appA,$appB" >> $OUTPUT
				size=$((size+1))
			fi
		done
	done
done

printf "\tcreating full factorial with $size runs ...\n"

for i in `seq 1 10`; do
	shuf $OUTPUT -o $OUTPUT
done
