which_loop=random_trk
obs=pt
for species in proton antiproton kplus kminus piplus piminus; do
  echo working on $species
  root -l -b -q highpt_mix.C\(\"${species}\",\"out-data/hadd_${which_loop}\",\"_smear\",\"${obs}\"\)
done
