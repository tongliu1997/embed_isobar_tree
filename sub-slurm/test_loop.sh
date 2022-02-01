#!/usr/bin/bash
#SBATCH  --job-name=test_loop
#SBATCH  --array=0-9
#SBATCH  -o out-slurm/%a

#SBATCH   --partition=day
#SBATCH   --time=00:10:00
#SBATCH   --mem=1G

n_events=-1
which_loop="test_loop"
dir="./out-data/test_loop/out-files"
inp_list="./in-lists/list_${SLURM_ARRAY_TASK_ID}.list"
name="${which_loop}"

./bin/main ${n_events} ${inp_list} ${name} ${dir}/${name}_${SLURM_ARRAY_TASK_ID}
