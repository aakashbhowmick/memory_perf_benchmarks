#include <benchmark/benchmark.h>
#include <vector>
#include <array>
#include <memory>

template< typename T, size_t SMALL_SIZE=5 >
class SSOVector
{
public:

    SSOVector():size_{0}
    {
    }

    void push_back(const T& val)
    {
        if(size_ == SMALL_SIZE)
            SwitchToVector_();

        if(UsingVector_())
            the_vector_->push_back(val);
        else
            the_array_[size_] = val;

        size_++;
    }

    T& operator[](size_t index)
    {
        return UsingVector_() ? the_vector_.at(index) : the_array_[index];
    }

    const T& operator[](size_t index) const
    {
        return UsingVector_() ? the_vector_.at(index) : the_array_[index];
    }

    size_t size() const
    {
       return size_;
    }

private:

    void SwitchToVector_()
    {
        the_vector_ = std::make_unique<std::vector<T>>(the_array_.begin(), the_array_.end());
    }

    bool UsingVector_()
    {
        return static_cast<bool>(the_vector_);
    }

private:
    size_t                          size_;
    std::array<T, SMALL_SIZE>       the_array_;
    std::unique_ptr<std::vector<T>> the_vector_;
};

template <size_t ARRAY_SIZE, size_t SMALL_SIZE>
void sso_construction(benchmark::State& state)
{
    const size_t num_objects = state.range(0);
    for(auto a: state)
    {
        for(size_t i=0; i < num_objects; ++i)
        {
            SSOVector<int, SMALL_SIZE> a;
            for(size_t j=0; j < ARRAY_SIZE; ++j) 
               a.push_back(j);
            benchmark::ClobberMemory();
        }
    }
}

BENCHMARK_TEMPLATE(sso_construction, 5, 0)->Unit(benchmark::kMicrosecond)->Arg(10000);
BENCHMARK_TEMPLATE(sso_construction, 5, 5)->Unit(benchmark::kMicrosecond)->Arg(10000);
