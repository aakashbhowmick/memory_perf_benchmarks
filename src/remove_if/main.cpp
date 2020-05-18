#include <benchmark/benchmark.h>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

std::set<size_t> get_fibonacci_till(size_t max)
{
    std::vector<size_t> fibs;
    fibs.push_back(1);
    fibs.push_back(1);
    while(fibs.back() < max)
    {
        fibs.push_back( *(fibs.end()) + *(fibs.end()-2));
    }

    std::set<size_t> fib_set(fibs.begin(), fibs.end());
    return fib_set;
}

/* Use std::vector::erase() */
void vector_erase(benchmark::State& state)
{
    const size_t max = state.range(0);

    std::set<size_t> fib_set = get_fibonacci_till(max);
    std::vector<size_t> int_array(max, 0);
    benchmark::DoNotOptimize(int_array);
    std::iota(int_array.begin(), int_array.end(), 1);

    for(auto a: state)
    {
        auto itr = int_array.begin();
        while(itr != int_array.end())
        {
            if( fib_set.find(*itr) != fib_set.end())
                itr = int_array.erase(itr);
            else
                ++itr;
        }
        benchmark::ClobberMemory();
    }
}


/* Use std::remove_if */
void vector_remove_if(benchmark::State& state)
{
    const size_t max = state.range(0);

    std::set<size_t> fib_set = get_fibonacci_till(max);
    std::vector<size_t> int_array(max, 0);
    benchmark::DoNotOptimize(int_array);
    std::iota(int_array.begin(), int_array.end(), 1);

    for(auto a: state)
    {
        auto end_itr = std::remove_if(int_array.begin(), int_array.end(), 
             [&](size_t i) -> bool {
                return fib_set.find(i) != fib_set.end();
             });
        int_array.resize(end_itr - int_array.begin());

        benchmark::ClobberMemory();
    }
}


BENCHMARK(vector_erase)->Unit(benchmark::kMicrosecond)->Arg(1000000);
BENCHMARK(vector_remove_if)->Unit(benchmark::kMicrosecond)->Arg(1000000);
