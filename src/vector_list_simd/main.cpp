#include <benchmark/benchmark.h>
#include <vector>
#include <list>
#include <numeric>


void vector_add(benchmark::State& state)
{

    const size_t count = state.range(0);
    std::vector<int> vect_of_ints(count);
    benchmark::DoNotOptimize(vect_of_ints);
    std::iota(vect_of_ints.begin(), vect_of_ints.end(), 0);

    for(auto a: state)
    {
        int sum = 0;
        for(size_t i=0; i < vect_of_ints.size(); ++i)
            sum += vect_of_ints[i];
    }
}

void list_add(benchmark::State& state)
{
    const size_t count = state.range(0);
    std::list<int> list_of_ints(count);
    benchmark::DoNotOptimize(list_of_ints);
    std::iota(list_of_ints.begin(), list_of_ints.end(), 0);

    for(auto a: state)
    {
        int sum = 0;
        for(auto itr = list_of_ints.begin(); itr != list_of_ints.end(); ++itr)
            sum += *itr;
    }
}

BENCHMARK(vector_add)->Unit(benchmark::kMillisecond)->Arg(1000000);
BENCHMARK(list_add)->Unit(benchmark::kMillisecond)->Arg(1000000);
