# cent_in=\{0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80\}
cent_in=\{0,10,20,40,60,80\}
ncent=5
pion_key=\"_pion\"
embed_key=\"\"

smear_key=\"_smear\"

for sys in ru zr
do
#    root -l -b -q ibu_fulldata.C\(\"${sys}\",-0.5,0.5,2,${embed_key},${cent_in}\)
#    root -l -b -q ibu_fulldata.C\(\"${sys}\",-0.5,0.5,1,${embed_key},${cent_in}\)
#    root -l -b -q ibu_fulldata.C\(\"${sys}\",-0.5,0.5,2,${pion_key},${cent_in}\)
#    root -l -b -q ibu_fulldata.C\(\"${sys}\",-0.5,0.5,2,${smear_key},${cent_in}\)


    nominal_name=\"outhist_${sys}_2_3_${ncent}bin.root\"
    iter_name=\"outhist_${sys}_2_3_${ncent}bin_1iter.root\"
    pion_name=\"outhist_${sys}_pion_2_3_${ncent}bin.root\"
    smear_name=\"outhist_${sys}_smear_2_3_${ncent}bin.root\"
    sys_name=\"systematics_${sys}_2_3_${ncent}bin.root\"

    root -l plot_systematics.C\(\"${sys}\",${nominal_name},${iter_name},${pion_name},${smear_name},${sys_name},${cent_in}\)

done

