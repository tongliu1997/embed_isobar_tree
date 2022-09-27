cent_in=\{0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80\}
ncent=16
# cent_in=\{0,10,20,40,60,80\}
# ncent=5
pion_key=\"_pion\"
embed_key=\"\"

smear_key=\"_smear\"
 for sys in ru zr 
 do
#    root -l -b -q ibu_fulldata.C\(\"${sys}\",-0.5,0.5,2,${embed_key},${cent_in}\)

#    root -l -b -q ibu_fulldata.C\(\"${sys}\",-0.5,0.5,2,${pion_key},${cent_in}\)
#    root -l -b -q ibu_fulldata.C\(\"${sys}\",-0.5,0.5,2,${smear_key},${cent_in}\)


    nominal_name=\"outhist_${sys}_2_3_${ncent}bin.root\"
    pion_name=\"outhist_${sys}_pion_2_3_${ncent}bin.root\"
    smear_name=\"outhist_${sys}_smear_2_3_${ncent}bin.root\"
    sys_name=\"systematics_${sys}_2_3_${ncent}bin.root\"

#    root -l -b -q outhist_systematics.C\(\"${sys}\",${nominal_name},${pion_name},${smear_name},${sys_name},${cent_in}\)

done

root -l  outhist_hgpythia.C\(\"outhist_ru_2_3_${ncent}bin.root\",\"outhist_zr_2_3_${ncent}bin.root\",\"systematics_ru_2_3_${ncent}bin.root\",\"systematics_zr_2_3_${ncent}bin.root\",${cent_in}\)

