
cd src/
if [[ ! -f ./a.out ]]
then
	g++ -O3 dist_hist.cpp
fi

for var in $(ls 0_samples)
do
    ./a.out 0_samples/${var}  1_dist_hist/$(echo ${var} |cut -d "." -f 1)
done

