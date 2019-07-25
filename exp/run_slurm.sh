#!/bin/bash

set -o errexit -o nounset -o pipefail -o posix

for step in `seq 1 15`; do
	start_name=`date +"%d/%m-%H:%M"`
	start_file=`date +"%d.%m-%H.%M"`
	#broadwell
#	sbatch --job-name="micro$step-($start_name)" --partition=tupi   --time=72:00:00 --output="slurm/tupi$step-($start_file).out"   --error="slurm/tupi.$step-($start_file).err"   time.batch
	#ivybridge
#	sbatch --job-name="micro$step-($start_name)" --partition=draco  --time=72:00:00 --output="slurm/draco$step-($start_file).out"  --error="slurm/draco.$step-($start_file).err"  time.batch
	#sandybridge
#	sbatch --job-name="micro$step-($start_name)" --partition=beagle --time=72:00:00 --output="slurm/beagle$step-($start_file).out" --error="slurm/beagle.$step-($start_file).err" time.batch
	#nehalem
#	sbatch --job-name="micro$step-($start_name)" --partition=turing --time=72:00:00 --output="slurm/turing$step-($start_file).out" --error="slurm/turing.$step-($start_file).err" time.batch
	#haswell
	sbatch --job-name="micro$step-($start_name)" --partition=hype   --time=72:00:00 --output="slurm/hype$step-($start_file).out"   --error="slurm/hype.$step-($start_file).err"   time.batch
done
