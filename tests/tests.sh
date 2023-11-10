obj="./tree_comp"

test_folder="../tests/"
test_files_names=("00.dat" "01.dat" "02.dat" "03.dat" "04.dat" "05.dat" "06.dat" "07.dat" "08.dat" "09.dat" "10.dat" "11.dat" "12.dat" "13.dat")

echo "TESTS:"
echo
for i in ${!test_files_names[@]}; do
    echo ${test_files_names[$i]}
    ${obj} < ${test_folder}${test_files_names[$i]}
    echo
done

