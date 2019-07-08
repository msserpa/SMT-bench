#!/usr/bin/env bash

set -o errexit -o nounset -o pipefail -o posix

#metrics=`papi_avail |grep Yes | awk {'print $1'} | sed ':a;N;$!ba;s/\n/ /g'`
metrics=(PAPI_L1_DCM PAPI_L1_ICM PAPI_L2_DCM PAPI_L2_ICM PAPI_L1_TCM PAPI_L2_TCM PAPI_L3_TCM PAPI_TLB_DM PAPI_TLB_IM PAPI_L1_LDM PAPI_L1_STM PAPI_L2_STM PAPI_STL_ICY PAPI_BR_UCN PAPI_BR_CN PAPI_BR_TKN PAPI_BR_NTK PAPI_BR_MSP PAPI_BR_PRC PAPI_TOT_INS PAPI_FP_INS PAPI_LD_INS PAPI_SR_INS PAPI_BR_INS PAPI_TOT_CYC PAPI_L2_DCH PAPI_L2_DCA PAPI_L3_DCA PAPI_L2_DCR PAPI_L3_DCR PAPI_L2_DCW PAPI_L3_DCW PAPI_L2_ICH PAPI_L2_ICA PAPI_L3_ICA PAPI_L2_ICR PAPI_L3_ICR PAPI_L2_TCA PAPI_L3_TCA PAPI_L2_TCR PAPI_L3_TCR PAPI_L2_TCW PAPI_L3_TCW PAPI_FDV_INS PAPI_FP_OPS PAPI_SP_OPS PAPI_DP_OPS PAPI_VEC_SP PAPI_VEC_DP PAPI_REF_CYC)
#metrics=(PAPI_TOT_INS PAPI_LD_INS PAPI_SR_INS PAPI_BR_INS PAPI_VEC_SP PAPI_VEC_DP)

for step in `seq 1 30`; do
	for i in ${!metrics[*]}; do
		metric=${metrics[$i]}
		sbatch --job-name="$metric.$step" --partition=beagle --time=72:00:00 --output="slurm/beagle.$metric.$step.out" --error="slurm/beagle.$metric.$step.err" papi.batch $metric $step
	done
done
