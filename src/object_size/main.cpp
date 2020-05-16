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


void object_access(benchmark::State& state)
{
    constexpr size_t vector_size = 1000000;
    std::vector<SizedObject<8>> object_vect(vector_size);
    for(auto a: state)
    {
        for(SizedObject<8>& obj : object_vect)
        {
            obj.SetByte(0, 'a');
            benchmark::ClobberMemory();
        }
    }
}

BENCHMARK(object_access);
