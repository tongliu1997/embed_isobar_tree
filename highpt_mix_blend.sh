which_loop=eff_phi
obs=phi
for species in proton antiproton kplus kminus piplus piminus; do
  echo working on $species
  root -l -b -q highpt_mix.C\(\"${species}\",\"out-data/hadd_${which_loop}\",\"${obs}\"\)
done
