#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <thread>

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
        std::vector<Point> point_list(count);
        benchmark::DoNotOptimize(point_list);
        state.ResumeTiming();

        std::thread t0([&]() mutable 
                    {
                        for(Point& pt : point_list)
                            pt.x += 1.0;
                    });

        std::thread t1([&]() mutable 
                    {
                        for(Point& pt : point_list)
                            pt.y += 1.0;
                    });

        std::thread t2([&]() mutable 
                    {
                        for(Point& pt : point_list)
                            pt.z += 1.0;
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
        std::vector<double> pt_x(count, 0.);
        std::vector<double> pt_y(count, 0.);
        std::vector<double> pt_z(count, 0.);
        benchmark::DoNotOptimize(pt_x);
        benchmark::DoNotOptimize(pt_y);
        benchmark::DoNotOptimize(pt_z);
        state.ResumeTiming();

        std::thread t0([&]() mutable 
                    {
                        for(double& x : pt_x)
                            x += 1.0;
                    });

        std::thread t1([&]() mutable 
                    {
                        for(double& y : pt_y)
                            y += 1.0;
                    });

        std::thread t2([&]() mutable 
                    {
                        for(double& z : pt_z)
                            z += 1.0;
                    });


        t0.join();
        t1.join();
        t2.join();
    }
}

BENCHMARK(with_false_sharing)->Unit(benchmark::kMillisecond)->UseRealTime()->Arg(1000000);
BENCHMARK(without_false_sharing)->Unit(benchmark::kMillisecond)->UseRealTime()->Arg(1000000);
