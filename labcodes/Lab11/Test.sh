mpic++ cannonParalell.cpp 
values=(1 2 3 4)

echo "Name: Nived krishna"
echo "Roll: 2021BCS0028"

echo "Number of Processes (np)     Matrix Size (N) Execution Time (sec)"
echo "                             N=3   N=10   N=100   N=500   N=1000"
#Loop through the array and run mpirun for each value

for value in "${values[@]}"; do
    mpirun -np "$value" ./a.out
done