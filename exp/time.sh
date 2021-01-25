#!/bin/bash

#set -o errexit -o nounset -o pipefail -o posix

host=`hostname | awk -F. {'print $1'}`
arch=`gcc-10.2 -march=native -Q --help=target | grep march | head -n1 | awk '{print $2}'`

date +"%d/%m/%Y %H:%M:%S"
printf "\t Running on $arch@$host \n\n"

date +"%d/%m/%Y %H:%M:%S"
exec=mixed.`hostname`.x
make -C .. &> /tmp/time.make
mv ../bin/$exec /tmp/$exec
exec=/tmp/$exec
sed 's/^/\t/' /tmp/time.make
printf "\n"

exit
mkdir -p output/
while true; do
	step=`ls output/ | grep $host | tail -1 | awk -F. {'print $2'}`
	if [ -z "$step" ]; then
		step=0
	fi

	doe=./DoE/$host.csv
	if [ -f "$doe" ]; then
	    printf "\t Using old $doe\n"
	else 
	    ./DoE.sh
	    step=$((step+1))
	fi

	output=./output/$host.$step.csv

	unset -v KMP_AFFINITY
	unset -v GOMP_CPU_AFFINITY
	unset -v OMP_NUM_THREADS
	unset -v OMP_SCHEDULE
	unset -v PAPI_EVENT
	unset -v LD_PRELOAD

	date +"%d/%m/%Y %H:%M:%S"
	printf "\t Warm-up\n"
	stress-ng --cpu 100 -t 5 &> /tmp/time.stress
	sed 's/^/\t/' /tmp/time.stress
	printf "\n"

	printf "\t Step: $step \n\n"

	while IFS=\; read -r thread mapping appA appB; do
		grepA=`echo $appA | awk -F: '{printf "%s", $1} NF > 1{printf "-%sKB", $2} {printf ":"}'`
		grepB=`echo $appB | awk -F: '{printf "%s", $1} NF > 1{printf "-%sKB", $2} {printf ":"}'`
		
		date +"%d/%m/%Y %H:%M:%S"
		printf "\t Mapping: $mapping \n"
		printf "\t Threads: $thread \n"
		printf "\t Application A: $appA \n"
		printf "\t Application B: $appB \n\n"
		OMP_NUM_THREADS=thread $exec $appA,$appB $mapping 30 1> /tmp/micro.time.out 2> /tmp/micro.time.err
		
		perfAmin=`cat /tmp/micro.time.err | grep $grepA\min | awk -F: {'printf "%f", $3'}`
		perfAmax=`cat /tmp/micro.time.err | grep $grepA\max | awk -F: {'printf "%f", $3'}`
		perfAavg=`cat /tmp/micro.time.err | grep $grepA\avg | awk -F: {'printf "%f", $3'}`

		echo $host,$arch,$thread,$mapping,$appA,$appB,$perfAmin,$perfAmax,$perfAavg >> $output

		sed -i '1d' $doe
        find $DOE -size 0 -delete

		[[ -s /tmp/micro.time.err ]] || echo "error"
	done < $doe

	date +"%d/%m/%Y %H:%M:%S"
	printf "\t done - $output \n\n"

	rm $doe
done

