#!/bin/bash

#set -o errexit -o nounset -o pipefail -o posix
chunk=100

for step in `seq 1 15`; do
	./DoE.R $step
	size=`cat DoE.$step.csv | wc -l`
	for begin in `seq 1 $chunk $size`; do
		end=$(($begin + $chunk - 1))
		#broadwell
	    sbatch --job-name="micro($step)-$begin:$end" --partition=tupi   --output="slurm/tupi.time.$step.$begin.$end.out"   --error="slurm/tupi.$step.$begin.$end.err"   time.batch $step $begin $end
		#ivybridge
		sbatch --job-name="micro($step)-$begin:$end" --partition=draco  --output="slurm/draco.time.$step.$begin.$end.out"  --error="slurm/draco.$step.$begin.$end.err"  time.batch $step $begin $end
		#sandybridge
		sbatch --job-name="micro($step)-$begin:$end" --partition=beagle --output="slurm/beagle.time.$step.$begin.$end.out" --error="slurm/beagle.$step.$begin.$end.err" time.batch $step $begin $end
		#nehalem
		sbatch --job-name="micro($step)-$begin:$end" --partition=turing --output="slurm/turing.time.$step.$begin.$end.out" --error="slurm/turing.$step.$begin.$end.err" time.batch $step $begin $end
		#haswell
		sbatch --job-name="micro($step)-$begin:$end" --partition=hype   --output="slurm/hype.time.$step.$begin.$end.out"   --error="slurm/hype.$step.$begin.$end.err"   time.batch $step $begin $end
	done
done