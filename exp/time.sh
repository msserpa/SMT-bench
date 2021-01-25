#!/bin/bash

#set -o errexit -o nounset -o pipefail -o posix

date +"%d/%m/%Y %H:%M:%S"
printf "\t Activating Intel Turbo Boost and Ondemand governor \n\n"

$SCRATCH/governor/utils --ondemand
$SCRATCH/governor/utils --turbo-on

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

	printf "\t Step: $step \n\n"

	while IFS=\; read -r thread mapping appA appB; do
		date +"%d/%m/%Y %H:%M:%S"
		printf "\t Warm-up\n"
		stress-ng --cpu 100 -t 3 &> /tmp/time.stress
		sed 's/^/\t  /' /tmp/time.stress
		printf "\n"
		sleep 2
	
		date +"%d/%m/%Y %H:%M:%S"
		printf "\t Mapping: $mapping \n"
		printf "\t Threads: $thread \n"
		printf "\t Application A: $appA \n"
		printf "\t Application B: $appB \n\n"
		OMP_NUM_THREADS=$thread $exec $appA,$appB $mapping 30 1> /tmp/micro.time.out 2> /tmp/micro.time.err
		
		perfAmin=`cat /tmp/micro.time.err | grep min | awk {'print $7'} | head -n1`
		perfAmax=`cat /tmp/micro.time.err | grep max | awk {'print $7'} | head -n1`
		perfAavg=`cat /tmp/micro.time.err | grep avg | awk {'print $7'} | head -n1`

		perfBmin=`cat /tmp/micro.time.err | grep min | awk {'print $7'} | tail -n1`
		perfBmax=`cat /tmp/micro.time.err | grep max | awk {'print $7'} | tail -n1`
		perfBavg=`cat /tmp/micro.time.err | grep avg | awk {'print $7'} | tail -n1`		

		echo $host,$arch,$thread,$mapping,$appA,$appB,$perfAmin,$perfAavg,$perfAmax,$perfBmin,$perfBavg,$perfBmax >> $output

		sed -i '1d' $doe
        find $DOE -size 0 -delete

		[[ -s /tmp/micro.time.err ]] || echo "error"
	done < $doe

	date +"%d/%m/%Y %H:%M:%S"
	printf "\t done - $output \n\n"

	rm $doe
done

