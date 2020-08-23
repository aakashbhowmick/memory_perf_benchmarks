#include <benchmark/benchmark.h>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>


/* std::vector iteration */
void vector_iteration(benchmark::State& state)
{
	size_t max = state.range(0);
	std::vector<size_t> int_array(max, 0);
    std::iota(int_array.begin(), int_array.end(), 1);
    for(auto a: state)
    {
        size_t sum=0;
        benchmark::DoNotOptimize(sum);
        for(size_t i=0; i < int_array.size(); ++i)
            sum += int_array[i];
        benchmark::ClobberMemory();
    }
}

/* std::set iteration */
void set_iteration(benchmark::State& state)
{
	size_t max = state.range(0);
	std::set<size_t> int_set;
    for(size_t i=0; i < max; ++i)
        int_set.insert(i+1);

    for(auto a: state)
    {
        size_t sum=0;
        benchmark::DoNotOptimize(sum);
        for(auto itr=int_set.begin(); itr != int_set.end(); ++itr)
            sum += *itr;
        benchmark::ClobberMemory();
    }
}


BENCHMARK(vector_iteration)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK(set_iteration)->Unit(benchmark::kMicrosecond)->Arg(10000);
