#include <benchmark/benchmark.h>
#include <vector>
#include <numeric>

std::vector<int> GetItems1()
{
    std::vector<int> items(5);
    std::iota(items.begin(), items.end(), 0);
    return items;
}

void GetItems2(std::vector<int>& items)
{
    items.resize(5);
    std::iota(items.begin(), items.end(), 0);
}

void without_reuse(benchmark::State& state)
{
    const size_t count = state.range(0);
    for(auto a: state)
    {
        int sum = 0;
        benchmark::DoNotOptimize(sum);
        for(size_t i=0; i < count; ++i)
        {
            std::vector<int> items = GetItems1();
            benchmark::DoNotOptimize(items);
            sum += items[0] + items[1] + items[2] + items[3] + items[4];
        }
    }
}


void with_reuse(benchmark::State& state)
{
    const size_t count = state.range(0);
    for(auto a: state)
    {
        int sum = 0;
        std::vector<int> items;
        benchmark::DoNotOptimize(sum);
        benchmark::DoNotOptimize(items);

        for(size_t i=0; i < count; ++i)
        {
            items.clear();
            GetItems2(items);
            sum += items[0] + items[1] + items[2] + items[3] + items[4];
        }
    }
}

BENCHMARK(without_reuse)->Unit(benchmark::kMillisecond)->Arg(1000000);
BENCHMARK(with_reuse)->Unit(benchmark::kMillisecond)->Arg(1000000);
