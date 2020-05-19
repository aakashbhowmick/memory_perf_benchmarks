#include <benchmark/benchmark.h>
#include <vector>
#include <SizedObject.h>


template <size_t OBJ_SIZE>
void object_access(benchmark::State& state)
{
    constexpr size_t vector_size = 10000;
    using SizedObjectN = SizedObject<OBJ_SIZE>;

    std::vector<SizedObjectN> object_vect(vector_size);
    for(auto a: state)
    {
        for(SizedObjectN& obj : object_vect)
        {
            obj.SetNthByte(0, 'a');
            benchmark::ClobberMemory();
        }
    }
}

BENCHMARK_TEMPLATE(object_access, 1<<3)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<4)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<5)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<6)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<7)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<8)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<9)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<10)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<11)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<12)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<13)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<14)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<15)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<16)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(object_access, 1<<17)->Unit(benchmark::kMillisecond);
