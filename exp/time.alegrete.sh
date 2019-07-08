#!/bin/bash

host=`hostname`
arch=`gcc -march=native -Q --help=target | grep march | awk '{print $2}'`

date +"%d/%m/%Y %H:%M:%S"
printf "\t Running on $host - $arch \n\n"

date +"%d/%m/%Y %H:%M:%S"
exec=mixed.$host
make -C .. &> /tmp/time.make
#mv ../bin/$exec $SCRATCH/$exec
exec=../bin/$exec
sed 's/^/\t/' /tmp/time.make
printf "\n"

unset -v KMP_AFFINITY
unset -v GOMP_CPU_AFFINITY
unset -v OMP_NUM_THREADS
unset -v OMP_SCHEDULE
unset -v PAPI_EVENT
unset -v LD_PRELOAD

app=(ctl-complex ctl-conditional ctl-random ctl-small-bbl ctl-switch dep-chain1 dep-chain2 dep-chain3 dep-chain4 dep-chain5 dep-chain6 fp-add fp-div fp-mul int-add int-div int-mul load-dep:16 load-dep:32 load-dep:64 load-dep:128 load-dep:256 load-dep:512 load-dep:1024 load-dep:2048 load-dep:4096 load-dep:8192 load-dep:16384 load-dep:32768 load-dep:65536 load-ind:16 load-ind:32 load-ind:64 load-ind:128 load-ind:256 load-ind:512 load-ind:1024 load-ind:2048 load-ind:4096 load-ind:8192 load-ind:16384 load-ind:32768 load-ind:65536 load-rand:16 load-rand:32 load-rand:64 load-rand:128 load-rand:256 load-rand:512 load-rand:1024 load-rand:2048 load-rand:4096 load-rand:8192 load-rand:16384 load-rand:32768 load-rand:65536 store-ind:16 store-ind:32 store-ind:64 store-ind:128 store-ind:256 store-ind:512 store-ind:1024 store-ind:2048 store-ind:4096 store-ind:8192 store-ind:16384 store-ind:32768 store-ind:65536 store-rand:16 store-rand:32 store-rand:64 store-rand:128 store-rand:256 store-rand:512 store-rand:1024 store-rand:2048 store-rand:4096 store-rand:8192 store-rand:16384 store-rand:32768 store-rand:65536)

date +"%d/%m/%Y %H:%M:%S"
printf "\t Warm-up\n\n"

$exec idle rand 5 &> /dev/null

for step in `seq 5 30`; do
 for mapping in heterogeneous homogeneous; do #rand
	for i in ${!app[*]}; do
		appA=${app[$i]}
		grepA=`echo $appA | awk -F: '{printf "%s", $1} NF > 1{printf "-%sKB", $2} {printf ":"}'`
		for j in ${!app[*]}; do
			appB=${app[$j]}
			grepB=`echo $appB | awk -F: '{printf "%s", $1} NF > 1{printf "-%sKB", $2} {printf ":"}'`
			if (( i <= j )); then
				date +"%d/%m/%Y %H:%M:%S"
				printf "\t Mapping: $mapping \n"
				printf "\t Application A: ${app[$i]} \n"
				printf "\t Application B: ${app[$j]} \n\n"
				$exec $appA,$appB $mapping 10 1> /tmp/micro.time.out 2> /tmp/micro.time.err
				if (( i == j )); then
					perfA=`cat /tmp/micro.time.err | grep $grepA | awk -F: {'printf "%d", $2/2'}`
					perfB=`cat /tmp/micro.time.err | grep $grepB  | awk -F: {'printf "%d", $2/2'}`
				else
					perfA=`cat /tmp/micro.time.err | grep $grepA  | awk -F: {'printf "%d", $2'}`
					perfB=`cat /tmp/micro.time.err | grep $grepB  | awk -F: {'printf "%d", $2'}`
				fi
				echo $host,$arch,$mapping,$appA,$appB,$perfA >> output/$host.$step.time
				echo $host,$arch,$mapping,$appB,$appA,$perfB >> output/$host.$step.time
				[[ -s /tmp/micro.time.err ]] || echo "error"
			fi
		done
	done
done
done

date +"%d/%m/%Y %H:%M:%S"
printf "\t done \n\n"
