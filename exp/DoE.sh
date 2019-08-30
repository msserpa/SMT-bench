#!/bin/bash

#set -o errexit -o nounset -o pipefail -o posix

declare -a MAPPING=("os" "homo" "hetero")
declare -a APP=("ctl-complex" "dep-chain1" "fp-add" "fp-div" "fp-mul" "int-add" "int-div" "int-mul" "load-dep:32" "load-ind:32" "load-rand:32" "load-dep:64" "load-ind:64" "load-rand:64" "load-dep:128" "load-ind:128" "load-rand:128" "load-dep:512" "load-ind:512" "load-rand:512" "load-dep:1024" "load-ind:1024" "load-rand:1024" "load-dep:2048" "load-ind:2048" "load-rand:2048" "load-dep:4096" "load-ind:4096" "load-rand:4096" "idle")
#declare -a APP=("ctl-complex" "dep-chain1" "fp-add" "fp-div" "fp-mul" "int-add" "int-div" "int-mul" "load-dep:16" "idle")
#declare -a APP=("ctl-complex" "ctl-conditional" "ctl-random" "ctl-small-bbl" "ctl-switch" "dep-chain1" "dep-chain2" "dep-chain3" "dep-chain4" "dep-chain5" "dep-chain6" "fp-add" "fp-div" "fp-mul" "int-add" "int-div" "int-mul" "load-dep:16" "load-ind:16" "load-rand:16" "load-dep:8192" "load-ind:8192" "load-rand:8192" "idle")

OUTPUT=./DoE/`hostname | awk -F. {'print $1'}`.csv
rm -f $OUTPUT

size=0
for map in "${MAPPING[@]}"; do
	for i in ${!APP[*]}; do
		appA=${APP[$i]}
		for j in ${!APP[*]}; do
			appB=${APP[$j]}
			if (( i < j )); then
				if [ $# -eq 1 ] && [ "$1" == "papi" ]; then
					declare -a PAPI=(`printf '%s\n' $(papi_avail |grep Yes | awk {'print $1'} | shuf | shuf) | sed s'/,\+$//' | tr '\n' ' '`)
					for event in "${PAPI[@]}"; do
						echo "$event;$map;$appA;$appB" >> $OUTPUT
						size=$((size+1))
					done
				else
					echo "$map;$appA;$appB" >> $OUTPUT
					size=$((size+1))
				fi
				
			fi
		done
	done
done
printf "\tcreating full factorial with $size runs ...\n"

for i in `seq 1 10`; do
	shuf $OUTPUT -o $OUTPUT
done
