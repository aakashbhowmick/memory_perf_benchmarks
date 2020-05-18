#include <benchmark/benchmark.h>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <iostream>

std::set<size_t> get_fibonacci_till(size_t max)
{
    std::vector<size_t> fibs;
    fibs.push_back(1);
    fibs.push_back(1);
    while(fibs.back() < max)
    {
        fibs.push_back( *(fibs.end()-1) + *(fibs.end()-2));
    }

    std::set<size_t> fib_set(fibs.begin(), fibs.end());
    return fib_set;
}

bool is_odd(size_t i)
{
    return i%2 == 1;
};

void print_vector(const std::vector<size_t>& v)
{
    for(size_t v_i : v)
        std::cout << v_i << " ";
    std::cout << std::endl;
}

/* Use std::vector::erase() */
void vector_erase(benchmark::State& state)
{
    const size_t max = state.range(0);

    std::set<size_t> fib_set = get_fibonacci_till(max);

    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        auto itr = int_array.begin();
        while(itr != int_array.end())
        {
            //if( fib_set.find(*itr) != fib_set.end())
            if(is_odd(*itr))
                itr = int_array.erase(itr);
            else
                ++itr;
        }
        benchmark::ClobberMemory();
        //print_vector(int_array);
    }
}


/* Use std::remove_if */
void vector_remove_if(benchmark::State& state)
{
    const size_t max = state.range(0);

    std::set<size_t> fib_set = get_fibonacci_till(max);

    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        auto end_itr = std::remove_if(int_array.begin(), int_array.end(), 
             [&](size_t i) -> bool {
                //return fib_set.find(i) != fib_set.end();
                return is_odd(i);
             });
        int_array.resize(end_itr - int_array.begin());

        benchmark::ClobberMemory();
        //print_vector(int_array);
    }
}

/* Copy to new vector */
void vector_copy_swap(benchmark::State& state)
{
    const size_t max = state.range(0);

    std::set<size_t> fib_set = get_fibonacci_till(max);

    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        std::vector<size_t> temp;
        for(size_t i : int_array)
        {
            if(!is_odd(i))
                temp.push_back(i);
        }
        int_array.swap(temp);

        benchmark::ClobberMemory();
        //print_vector(int_array);
    }
}


BENCHMARK(vector_erase)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK(vector_remove_if)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK(vector_copy_swap)->Unit(benchmark::kMicrosecond)->Arg(10000);
