
n_events=-1
which_loop="random_trk"
dir="."
# inp_list="./in-lists/list_test.list"
name="${which_loop}"

species=piplus
inp_list="./lists/test_${species}.list"

while read line; do
  echo $line
done < $inp_list

echo $inp_list
./bin/main ${n_events} ${inp_list} ${name} ${dir}/${name}_${species} 
