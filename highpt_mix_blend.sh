for species in proton antiproton kplus kminus piplus piminus; do
  echo working on $species
  root -l -b -q highpt_mix.C\(\"${species}\"\)
done
