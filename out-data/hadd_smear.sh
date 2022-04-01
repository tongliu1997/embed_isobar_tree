if [ $# -ge 1 ]; then
    which_loop=$1
else
    which_loop=random_trk
fi

if [ -d ${which_loop}/smear_highpt ]; then
    rm ${which_loop}/smear_highpt/*
else
    mkdir ${which_loop}/smear_highpt
fi



mv ${which_loop}/smear/*_highpt_*.root ${which_loop}/smear_highpt

echo High pt files moved.


for species in piplus piminus kplus kminus proton antiproton
do
  hadd -f hadd_${which_loop}_${species}_smear.root ${which_loop}/smear/${which_loop}_${species}_*.root 
  hadd -f hadd_${which_loop}_${species}_highpt_smear.root ${which_loop}/smear_highpt/${which_loop}_${species}_highpt_*.root
done

mv ${which_loop}/smear_highpt/*.root ${which_loop}/smear/
rm -r ${which_loop}/smear_highpt
