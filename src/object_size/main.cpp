#include <benchmark/benchmark.h>
#include <vector>

/* Creates a class of given size in bytes */
template <size_t BYTES>
class SizedObject
{
public:
    void SetByte(size_t byte_index, char val)
    {
        bytes[byte_index] = val;
    }

private:
    char bytes[BYTES];
};


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
            obj.SetByte(0, 'a');
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
