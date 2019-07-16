#!/bin/bash

host=`hostname`
arch=`gcc -march=native -Q --help=target | grep march | awk '{print $2}'`

date +"%d/%m/%Y %H:%M:%S"
printf "\t Running on $arch@$host \n\n"

date +"%d/%m/%Y %H:%M:%S"
exec=mixed.$host
make -C .. &> /tmp/time.make
mv ../bin/$exec /tmp/$exec
exec=/tmp/$exec
sed 's/^/\t/' /tmp/time.make
printf "\n"

unset -v KMP_AFFINITY
unset -v GOMP_CPU_AFFINITY
unset -v OMP_NUM_THREADS
unset -v OMP_SCHEDULE
unset -v PAPI_EVENT
unset -v LD_PRELOAD


for step in `seq 1 10`; do
	date +"%d/%m/%Y %H:%M:%S"
	printf "\t Warm-up\n"
	stress-ng --cpu 1000 -t 5 &> /dev/null
	while IFS=, read -r mapping appA appB; do
		echo $step $mapping $appA $appB

		grepA=`echo $appA | awk -F: '{printf "%s", $1} NF > 1{printf "-%sKB", $2} {printf ":"}'`
		grepB=`echo $appB | awk -F: '{printf "%s", $1} NF > 1{printf "-%sKB", $2} {printf ":"}'`
		
		date +"%d/%m/%Y %H:%M:%S"
		printf "\t Mapping: $mapping \n"
		printf "\t Application A: $appA \n"
		printf "\t Application B: $appB \n\n"
		$exec $appA,$appB $mapping B 1> /tmp/micro.time.out 2> /tmp/micro.time.err
		
		if [ "$appA" == "$appB" ]; then
			perfAmin=`cat /tmp/micro.time.err | grep $grepA\min | awk -F: {'printf "%f", $3 / 2.0'}`
			perfAmax=`cat /tmp/micro.time.err | grep $grepA\max | awk -F: {'printf "%f", $3 / 2.0'}`
			perfAavg=`cat /tmp/micro.time.err | grep $grepA\avg | awk -F: {'printf "%f", $3 / 2.0'}`

			perfBmin=`cat /tmp/micro.time.err | grep $grepB\min | awk -F: {'printf "%f", $3 / 2.0'}`
			perfBmax=`cat /tmp/micro.time.err | grep $grepB\max | awk -F: {'printf "%f", $3 / 2.0'}`
			perfBavg=`cat /tmp/micro.time.err | grep $grepB\avg | awk -F: {'printf "%f", $3 / 2.0'}`
		else
			perfAmin=`cat /tmp/micro.time.err | grep $grepA\min | awk -F: {'printf "%f", $3'}`
			perfAmax=`cat /tmp/micro.time.err | grep $grepA\max | awk -F: {'printf "%f", $3'}`
			perfAavg=`cat /tmp/micro.time.err | grep $grepA\avg | awk -F: {'printf "%f", $3'}`

			perfBmin=`cat /tmp/micro.time.err | grep $grepB\min | awk -F: {'printf "%f", $3'}`
			perfBmax=`cat /tmp/micro.time.err | grep $grepB\max | awk -F: {'printf "%f", $3'}`
			perfBavg=`cat /tmp/micro.time.err | grep $grepB\avg | awk -F: {'printf "%f", $3'}`
		fi
		echo $host,$arch,$mapping,$appA,$appB,$perfAmin,$perfAmax,$perfAavg >> output/$host.$step.time
		echo $host,$arch,$mapping,$appB,$appA,$perfBmin,$perfBmax,$perfBavg >> output/$host.$step.time
		[[ -s /tmp/micro.time.err ]] || echo "error"	
	done < DoE.alegrete.csv
done

date +"%d/%m/%Y %H:%M:%S"
printf "\t done \n\n"
