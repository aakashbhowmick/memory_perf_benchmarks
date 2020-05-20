# memory_perf_benchmarks
Some performance benchmark tests on various memory access patterns

## Dependencies
1. [ Google Benchmark ](https://github.com/google/benchmark) 

## Compiling
1. Clone the repository : `git clone https://github.com/aakashbhowmick/memory_perf_benchmarks.git`. This should create a directory `memory_perf_benchmarks`. 
2. Create a new directory `memory_perf_benchmarks/build` for out of source build, run `cmake` and compile :
```shell
cd memory_perf_benchmarks`
mkdir build & cd build
cmake ..
make
```

## Running benchmarks
Name of benchmark executable is same as name of directory under `src` and is placed under `build` directly on compiling.
```shell
# Run branch_mispredict
cd build
./branch_predict
```

## Accuracy of measurements
You might need to turn-off CPU scaling for more accurate results.
```shell
sudo cpupower frequency-set --governor performance
./branch_predict
sudo cpupower frequency-set --governor powersave
```
