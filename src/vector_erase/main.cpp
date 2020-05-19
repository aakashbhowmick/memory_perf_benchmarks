#include <benchmark/benchmark.h>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>

#define REMOVE_CONDITION 2

class TestFixture : public benchmark::Fixture
{
    static std::set<size_t> fib_set;
public:
    void SetUp(const ::benchmark::State& state)
    {
        fib_set = get_fibonacci_till(state.range(0));
    }

    void TearDown(const ::benchmark::State& state)
    {
    }

    static bool RemoveThis(size_t i)
    {
#if REMOVE_CONDITION==1
        return fib_set.find(i) != fib_set.end();
#elif REMOVE_CONDITION==2
        return is_odd(i);
#elif REMOVE_CONDITION==3
        return is_multiple_10(i);
#elif REMOVE_CONDITION==4
        return is_multiple_100(i);
#endif
    }

private:

    static std::set<size_t> get_fibonacci_till(size_t max)
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

    static bool is_odd(size_t i)
    {
        return i%2 == 1;
    };

    static bool is_multiple_10(size_t i)
    {
        return i%10 == 0;
    }

    static bool is_multiple_100(size_t i)
    {
        return i%100 == 0;
    }

};
std::set<size_t> TestFixture::fib_set;


/* Use std::vector::erase() */
BENCHMARK_DEFINE_F(TestFixture, vector_erase)(benchmark::State& state)
{
    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        size_t max = state.range(0);
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        auto itr = int_array.begin();
        while(itr != int_array.end())
        {
            if(RemoveThis(*itr))
                itr = int_array.erase(itr);
            else
                ++itr;
        }
        benchmark::ClobberMemory();
    }
}


/* Use std::remove_if */
BENCHMARK_DEFINE_F(TestFixture, vector_remove_if)(benchmark::State& state)
{
    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        size_t max = state.range(0);
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        auto end_itr = std::remove_if(int_array.begin(), int_array.end(), RemoveThis);
        int_array.resize(end_itr - int_array.begin());

        benchmark::ClobberMemory();
    }
}

/* Copy to new vector */
BENCHMARK_DEFINE_F(TestFixture, vector_copy_swap)(benchmark::State& state)
{
    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        size_t max = state.range(0);
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        std::vector<size_t> temp;
        for(size_t i : int_array)
        {
            if(!RemoveThis(i))
                temp.push_back(i);
        }
        int_array.swap(temp);

        benchmark::ClobberMemory();
    }
}

BENCHMARK_DEFINE_F(TestFixture, set_erase)(benchmark::State& state)
{
    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        size_t max = state.range(0);
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        std::set<size_t> test_set;
        test_set.insert(int_array.begin(), int_array.end());
        state.ResumeTiming(); // RESUME TIMING

        auto itr = test_set.begin();
        while(itr != test_set.end())
        {
            if(RemoveThis(*itr))
            {
                itr = test_set.erase(itr);
            }
            else
            {
                ++itr;
            }
        }

        benchmark::ClobberMemory();
    }
}


BENCHMARK_DEFINE_F(TestFixture, set_difference)(benchmark::State& state)
{
    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        size_t max = state.range(0);
        std::vector<size_t> int_array(max, 0);
        benchmark::DoNotOptimize(int_array);
        std::iota(int_array.begin(), int_array.end(), 1);
        std::set<size_t> test_set;
        test_set.insert(int_array.begin(), int_array.end());
        state.ResumeTiming(); // RESUME TIMING

        auto itr = test_set.begin();
        std::set<size_t> removal_set;
        for(auto itr = test_set.begin(); itr != test_set.end(); ++itr)
        {
            if(RemoveThis(*itr))
                removal_set.insert(*itr);
        }
        std::vector<size_t> diff_set;
        diff_set.resize(test_set.size() - removal_set.size());
        std::set_difference(test_set.begin(), test_set.end(),
                            removal_set.begin(), removal_set.end(),
                            diff_set.begin());

        benchmark::ClobberMemory();
    }
}


BENCHMARK_DEFINE_F(TestFixture, list_erase)(benchmark::State& state)
{
    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        size_t max = state.range(0);
        std::list<size_t> int_list(max, 0);
        benchmark::DoNotOptimize(int_list);
        std::iota(int_list.begin(), int_list.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        auto itr = int_list.begin();
        while(itr != int_list.end())
        {
            if(RemoveThis(*itr))
                itr = int_list.erase(itr);
            else
                ++itr;
        }
        benchmark::ClobberMemory();
    }
}

BENCHMARK_DEFINE_F(TestFixture, list_remove_if)(benchmark::State& state)
{
    for(auto a: state)
    {
        state.PauseTiming();  // PAUSE TIMING
        size_t max = state.range(0);
        std::list<size_t> int_list(max, 0);
        benchmark::DoNotOptimize(int_list);
        std::iota(int_list.begin(), int_list.end(), 1);
        state.ResumeTiming(); // RESUME TIMING

        auto end_itr = std::remove_if(int_list.begin(), int_list.end(), RemoveThis);
        int_list.resize(std::distance(end_itr, int_list.begin()));

        benchmark::ClobberMemory();
    }
}


BENCHMARK_REGISTER_F(TestFixture, vector_erase)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK_REGISTER_F(TestFixture, vector_remove_if)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK_REGISTER_F(TestFixture, vector_copy_swap)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK_REGISTER_F(TestFixture, set_erase)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK_REGISTER_F(TestFixture, set_difference)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK_REGISTER_F(TestFixture, list_erase)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK_REGISTER_F(TestFixture, list_remove_if)->Unit(benchmark::kMicrosecond)->Arg(10000);
