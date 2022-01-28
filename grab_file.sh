file_dir=/gpfs/loomis/project/caines/tl543/isobar_embed
list_dir=./lists
nlists=30
if [ ! -d $file_dir ]; then
  echo Folder does not even exist.
fi

if [ ! -d $list_dir ]; then
  mkdir $list_dir
# elif [ ! -e $list_dir ]; then
fi

for species in piplus piminus kplus kminus proton antiproton piplus_highpt piminus_highpt kplus_highpt kminus_highpt proton_highpt antiproton_highpt
do 
  if [[ "${species}" =~ .*"highpt".* ]]; then
    file_dir=/gpfs/loomis/project/caines/tl543/isobar_highpt_embed
    nlists=5
  else
    file_dir=/gpfs/loomis/project/caines/tl543/isobar_embed
    nlists=30
  fi
  if [ -f $list_dir/total_list_${species}.list ]; then
    rm $list_dir/total_list_${species}.list
  fi

  ls $file_dir/${species}_*.root > $list_dir/total_list_${species}.list

  echo "total_list for ${species} grabbed."

  if [  `ls -1 $list_dir/list_${species}_*.list 2>/dev/null | wc -l` -gt 0 ]; then
    rm $list_dir/list_${species}_*.list
  fi

# nlists=$(($nlists-1))

  i=0

  while read line; do
    echo $line >> $list_dir/list_${species}_${i}.list
    i=$(($i+1))
    if [ "$i" -ge "$nlists" ]; then
      i=0
    fi
  done < $list_dir/total_list_${species}.list
done
