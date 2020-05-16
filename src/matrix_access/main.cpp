#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <numeric>


void sequential_access(benchmark::State& state)
{
    const size_t vector_size = state.range(0);
    std::vector<size_t> object_vect(vector_size, 0);
    for(auto a: state)
    {
        for(size_t i=0; i < object_vect.size(); ++i)
        {
            object_vect[i] = 1;
            benchmark::ClobberMemory();
        }
    }
}

void random_access(benchmark::State& state)
{
    const size_t vector_size = state.range(0);
    std::vector<size_t> object_vect(vector_size, 0);
    std::vector<size_t> positions(vector_size, 0);
    std::iota(positions.begin(), positions.end(), 0);
    std::random_shuffle(positions.begin(), positions.end());

    for(auto a: state)
    {
        for(size_t i=0; i < positions.size(); ++i)
        {
            object_vect[positions[i]] = 1;
            benchmark::ClobberMemory();
        }
    }
}

BENCHMARK(sequential_access)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK(random_access)->Unit(benchmark::kMicrosecond)->Arg(10000);
