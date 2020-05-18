#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <numeric>


void new_vector(benchmark::State& state)
{
    const size_t count = state.range(0);
    for(auto a: state)
    {
        for(size_t i=0; i < count; ++i)
        {
            std::vector<int> array;
            benchmark::DoNotOptimize(array);

            for(size_t j=0; j < 5; ++j)
                array.push_back(j);
            benchmark::ClobberMemory();
        }
    }
}

void reuse_vector(benchmark::State& state)
{
    const size_t count = state.range(0);
    std::vector<int> array;
    benchmark::DoNotOptimize(array);

    for(auto a: state)
    {
        for(size_t i=0; i < count; ++i)
        {
            array.clear();
            for(size_t j=0; j < 5; ++j)
                array.push_back(j);
            benchmark::ClobberMemory();
        }
    }
}


BENCHMARK(new_vector)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK(reuse_vector)->Unit(benchmark::kMicrosecond)->Arg(10000);
