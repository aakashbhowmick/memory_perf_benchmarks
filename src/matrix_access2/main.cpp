#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <numeric>


void sequential(benchmark::State& state)
{
    const size_t size = state.range(0);
    std::vector<std::vector<size_t>> matrix(size);
    for(size_t i=0; i < matrix.size(); ++i)
        matrix[i].resize(size, i);

    for(auto a: state)
    {
        size_t sum = 0;
        benchmark::DoNotOptimize(sum);
        for(size_t i=0; i < size; ++i)
        {
            for(size_t j=0; j < size; ++j)
                sum += matrix[i][j];
        }
    }
}


void non_sequential(benchmark::State& state)
{
    const size_t size = state.range(0);
    std::vector<std::vector<size_t>> matrix(size);
    for(size_t i=0; i < matrix.size(); ++i)
        matrix[i].resize(size, i);

    for(auto a: state)
    {
        size_t sum = 0;
        benchmark::DoNotOptimize(sum);
        for(size_t i=0; i < size; ++i)
        {
            for(size_t j=0; j < size; ++j)
                sum += matrix[j][i];
        }
    }
}


BENCHMARK(sequential)->Unit(benchmark::kMillisecond)->Arg(10000);
BENCHMARK(non_sequential)->Unit(benchmark::kMillisecond)->Arg(10000);
