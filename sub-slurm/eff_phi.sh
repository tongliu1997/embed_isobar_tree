#!/usr/bin/bash
#SBATCH  --job-name=eff_phi
#SBATCH  --array=0-209
#SBATCH  -o out-slurm/%a

#SBATCH   --partition=day
#SBATCH   --time=00:10:00
#SBATCH   --mem=1G

n_events=-1
species_list=("piplus" "piminus" "kplus" "kminus" "proton" "antiproton")
species_id=$((${SLURM_ARRAY_TASK_ID}/35))
list_id=$((${SLURM_ARRAY_TASK_ID}%35))
species=${species_list[${species_id}]}
if [[ ${list_id} -ge 30 ]]; then
  list_id=$((${list_id}-30))
  species="${species}_highpt"
fi


which_loop="eff_phi"
dir="./out-data/${which_loop}"
inp_list="./lists/list_${species}_${list_id}.list"
name="${which_loop}"
echo ${species} ${list_id}
./bin/main ${n_events} ${inp_list} ${name} ${dir}/${name}_${species}_${list_id}
