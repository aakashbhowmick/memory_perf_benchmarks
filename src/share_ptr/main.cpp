#include <benchmark/benchmark.h>
#include <vector>
#include <list>
#include <numeric>
#include <memory>
#include <thread>

using IntVect = std::vector<int>;

int sum_till_val(const std::shared_ptr<IntVect> vect_ptr,
                int index)
{
    int sum = 0;
    for(size_t i=0; i <= index; ++i)
        sum += vect_ptr->at(i);

    return sum;
}

int sum_till_ref(const std::shared_ptr<IntVect>& vect_ptr,
                int index)
{
    int sum = 0;
    for(size_t i=0; i <= index; ++i)
        sum += vect_ptr->at(i);
    
    return sum;
}


void shared_ptr_by_value(benchmark::State& state)
{

    const size_t count = state.range(0);
    std::shared_ptr<IntVect> vect_of_ints = std::make_shared<IntVect>(count);
    benchmark::DoNotOptimize(vect_of_ints);
    std::iota(vect_of_ints->begin(), vect_of_ints->end(), 0);

    std::vector<int> sums_0;
    std::vector<int> sums_1;
    benchmark::DoNotOptimize(sums_0);
    benchmark::DoNotOptimize(sums_1);

    for(auto a: state)
    {
        sums_0.clear();
        sums_1.clear();

        std::thread t0([&]()
                    {
                        for(size_t i=0; i < vect_of_ints->size()/2; i++)
                        {
                            int cumulative_sum = sum_till_val(vect_of_ints, i);
                            sums_0.push_back(cumulative_sum);
                        }
                    });

        std::thread t1([&]()
                    {
                        for(size_t i=vect_of_ints->size()/2; i < vect_of_ints->size(); i++)
                        {
                            int cumulative_sum = sum_till_val(vect_of_ints, i);
                            sums_1.push_back(cumulative_sum);
                        }
                    });
        
    }
}


void shared_ptr_by_ref(benchmark::State& state)
{

    const size_t count = state.range(0);
    std::shared_ptr<IntVect> vect_of_ints = std::make_shared<IntVect>(count);
    benchmark::DoNotOptimize(vect_of_ints);
    std::iota(vect_of_ints->begin(), vect_of_ints->end(), 0);

    std::vector<int> sums_0;
    std::vector<int> sums_1;
    benchmark::DoNotOptimize(sums_0);
    benchmark::DoNotOptimize(sums_1);

    for(auto a: state)
    {
        sums_0.clear();
        sums_1.clear();

        std::thread t0([&]()
                    {
                        for(size_t i=0; i < vect_of_ints->size()/2; i++)
                        {
                            int cumulative_sum = sum_till_ref(vect_of_ints, i);
                            sums_0.push_back(cumulative_sum);
                        }
                    });

        std::thread t1([&]()
                    {
                        for(size_t i=vect_of_ints->size()/2; i < vect_of_ints->size(); i++)
                        {
                            int cumulative_sum = sum_till_ref(vect_of_ints, i);
                            sums_1.push_back(cumulative_sum);
                        }
                    });
        
    }
}



BENCHMARK(shared_ptr_by_value)->Unit(benchmark::kMillisecond)->Arg(1000000)->UseRealTime();
BENCHMARK(shared_ptr_by_ref)->Unit(benchmark::kMillisecond)->Arg(1000000)->UseRealTime();
