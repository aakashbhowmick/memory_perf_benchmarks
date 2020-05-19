#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <numeric>

struct Point
{
    double x;
    double y;
    double z;

    Point():x{0.}, y{0.}, z{0.}
    {
    }
};

void with_false_sharing(benchmark::State& state)
{
    const size_t count = state.range(0);

    for(auto a : state)
    {
        state.PauseTiming();
        std::vector<double> coeffs(5);
        std::iota(coeffs.begin(), coeffs.end(), 0);
        std::vector<Point> point_list(count);
        benchmark::DoNotOptimize(point_list);
        state.ResumeTiming();

        std::thread t0([&]() mutable 
                    {
                        for(size_t i=0; i < point_list.size(); ++i)
                            point_list[i].x += coeffs[i%5];
                    });

        std::thread t1([&]() mutable 
                    {
                        for(size_t i=0; i < point_list.size(); ++i)
                            point_list[i].y += coeffs[i%5];
                    });

        std::thread t2([&]() mutable 
                    {
                        for(size_t i=0; i < point_list.size(); ++i)
                            point_list[i].z += coeffs[i%5];
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

        std::vector<double> coeffs(5);
        std::iota(coeffs.begin(), coeffs.end(), 0);

        std::vector<double> pt_x(count, 0.);
        std::vector<double> pt_y(count, 0.);
        std::vector<double> pt_z(count, 0.);
        benchmark::DoNotOptimize(pt_x);
        benchmark::DoNotOptimize(pt_y);
        benchmark::DoNotOptimize(pt_z);
        state.ResumeTiming();

        std::thread t0([&]() mutable 
                    {
                        for(size_t i=0; i < pt_x.size(); ++i)
                            pt_x[i] += coeffs[i%5];
                    });

        std::thread t1([&]() mutable 
                    {
                        for(size_t i=0; i < pt_y.size(); ++i)
                            pt_y[i] += coeffs[i%5];
                    });

        std::thread t2([&]() mutable 
                    {
                        for(size_t i=0; i < pt_z.size(); ++i)
                            pt_z[i] += coeffs[i%5];
                    });



        t0.join();
        t1.join();
        t2.join();
    }
}

BENCHMARK(with_false_sharing)->Unit(benchmark::kMillisecond)->UseRealTime()->Arg(1000000);
BENCHMARK(without_false_sharing)->Unit(benchmark::kMillisecond)->UseRealTime()->Arg(1000000);
