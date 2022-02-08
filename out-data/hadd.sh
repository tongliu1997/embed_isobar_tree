if [ $# -ge 1 ]; then
    which_loop=$1
else
    which_loop=random_trk
fi

if [ -d ${which_loop}_highpt ]; then
    rm ${which_loop}_highpt/*
else
    mkdir ${which_loop}_highpt
fi



mv ${which_loop}/*_highpt_*.root ${which_loop}_highpt

echo High pt files moved.


for species in piplus piminus kplus kminus proton antiproton
do
  hadd -f hadd_${which_loop}_${species}.root ${which_loop}/${which_loop}_${species}_*.root 
  hadd -f hadd_${which_loop}_${species}_highpt.root ${which_loop}_highpt/${which_loop}_${species}_highpt_*.root
done

mv ${which_loop}_highpt/*.root ${which_loop}
rm -r ${which_loop}_highpt
