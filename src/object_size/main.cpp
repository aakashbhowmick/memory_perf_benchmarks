#include <benchmark/benchmark.h>
#include <string>

void string_creation(benchmark::State& state)
{
    for(auto a: state)
        std::string str("Hello World");
}

BENCHMARK(string_creation);
