#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <numeric>


void branch_predict_bad(benchmark::State& state)
{
    const size_t count = state.range(0);
    std::vector<size_t> a(count, 1);
    std::vector<size_t> b(count, 2);
    std::vector<size_t> c(count, 3);

    std::vector<size_t> all;
    all.insert(all.end(), a.begin(), a.end());
    all.insert(all.end(), b.begin(), b.end());
    all.insert(all.end(), c.begin(), c.end());
    std::random_shuffle(all.begin(), all.end());

    for(auto a: state)
    {
        size_t sum = 0;
        benchmark::DoNotOptimize(sum);
        for(size_t i=0; i < all.size(); ++i)
        {
            if(all[i] == 1)
                sum += 1;
            else if(all[i] == 2)
                sum += 5;
            else if(all[i] == 3)
                sum += 8;
        }
    }
}


void branch_predict_good(benchmark::State& state)
{
    const size_t count = state.range(0);
    std::vector<size_t> a(count, 1);
    std::vector<size_t> b(count, 2);
    std::vector<size_t> c(count, 3);

    std::vector<size_t> all;
    all.insert(all.end(), a.begin(), a.end());
    all.insert(all.end(), b.begin(), b.end());
    all.insert(all.end(), c.begin(), c.end());

    for(auto a: state)
    {
        size_t sum = 0;
        benchmark::DoNotOptimize(sum);
        for(size_t i=0; i < all.size(); ++i)
        {
            if(all[i] == 1)
                sum += 1;
            else if(all[i] == 2)
                sum += 5;
            else if(all[i] == 3)
                sum += 8;
        }
    }
}


BENCHMARK(branch_predict_bad)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK(branch_predict_good)->Unit(benchmark::kMicrosecond)->Arg(10000);
