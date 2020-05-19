#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <numeric>
#include <cstdlib>

struct Point
{
    double xyz[3];

    Point()
    {
        xyz[0] = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        xyz[1] = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        xyz[2] = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    }

    const double& operator[] (size_t i) const
    {
        return xyz[i];
    }

};

void with_false_sharing(benchmark::State& state)
{
    const size_t count = state.range(0);

    for(auto a : state)
    {
        state.PauseTiming();
        std::vector<Point> point_list(count);
        benchmark::DoNotOptimize(point_list);
        state.ResumeTiming();

        double sum[3];
        sum[0] = sum[1] = sum[2] = 0.;

        std::thread t0([&]() mutable 
                    {
                        for(size_t i=0; i < point_list.size(); ++i)
                            sum[0] += point_list[i][0];
                    });

        std::thread t1([&]() mutable 
                    {
                        for(size_t i=0; i < point_list.size(); ++i)
                            sum[1] += point_list[i][1];
                    });

        std::thread t2([&]() mutable 
                    {
                        for(size_t i=0; i < point_list.size(); ++i)
                            sum[2] += point_list[i][2];
                    });


        t0.join();
        t1.join();
        t2.join();
    }
}


void without_false_sharing(benchmark::State& state)
{
    const size_t count = state.range(0);

    for(auto a : state)
    {
        state.PauseTiming();
        std::vector<Point> point_list(count);
        benchmark::DoNotOptimize(point_list);
        state.ResumeTiming();

        double sum[3];
        sum[0] = sum[1] = sum[2] = 0.0;

        std::thread t0([&]() mutable 
                    {
                        double thread_sum = 0;
                        for(size_t i=0; i < point_list.size(); ++i)
                            thread_sum += point_list[i][0];
                        sum[0] = thread_sum;
                    });

        std::thread t1([&]() mutable 
                    {
                        double thread_sum = 0;
                        for(size_t i=0; i < point_list.size(); ++i)
                            thread_sum += point_list[i][1];
                        sum[1] = thread_sum;
                    });

        std::thread t2([&]() mutable 
                    {
                        double thread_sum = 0;
                        for(size_t i=0; i < point_list.size(); ++i)
                            thread_sum += point_list[i][2];
                        sum[2] = thread_sum;
                    });


        t0.join();
        t1.join();
        t2.join();
    }
}

BENCHMARK(with_false_sharing)->Unit(benchmark::kMillisecond)->UseRealTime()->Arg(1000000);
BENCHMARK(without_false_sharing)->Unit(benchmark::kMillisecond)->UseRealTime()->Arg(1000000);
