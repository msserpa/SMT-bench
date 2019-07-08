#!/usr/bin/env bash

set -o errexit -o nounset -o pipefail -o posix

for step in `seq 1 30`; do
	#broadwell
    sbatch --job-name="micro.time.$step" --partition=tupi --time=72:00:00 --output="slurm/tupi.time.$step.out" --error="slurm/tupi.time.$step.err" time.batch $step
	#ivybridge
	sbatch --job-name="micro.time.$step" --partition=draco --time=72:00:00 --output="slurm/draco.time.$step.out" --error="slurm/draco.time.$step.err" time.batch $step
	#sandybridge
	sbatch --job-name="micro.time.$step" --partition=beagle --time=72:00:00 --output="slurm/beagle.time.$step.out" --error="slurm/beagle.time.$step.err" time.batch $step
	#nehalem
	sbatch --job-name="micro.time.$step" --partition=turing --time=72:00:00 --output="slurm/turing.time.$step.out" --error="slurm/turing.time.$step.err" time.batch $step
	#haswell
	sbatch --job-name="micro.time.$step" --partition=hype --time=72:00:00 --output="slurm/hype.time.$step.out" --error="slurm/hype.time.$step.err" time.batch $step
done
