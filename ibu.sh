 cent_in=\{0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80\}
# cent_in=\{0,10,20,30,40,50,60,70,80\}
#cent_in=\{0,10,20,40,60,80\}
# embed_key=\"_pion\"
embed_key=\"\"
# root -l -b -q ibu_fulldata.C\(0,-1,1,2,${cent_in}\)
# root -l -b -q ibu_fulldata.C\(1,-1,1,2,${cent_in}\)
#root -l -b -q ibu_fulldata.C\(0,-0.5,0.5,2,${embed_key},${cent_in}\)
# root -l -b -q ibu_fulldata.C\(1,-0.5,0.5,2,${embed_key},${cent_in}\)


root -l outhist_plot.C\(\"outhist_ru_2_3.root\",\"outhist_zr_2_3.root\",${cent_in}\)

