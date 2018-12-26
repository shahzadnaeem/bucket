
#pragma once

#include <chrono>
#include <regex>
#include <vector>

#include <cstdlib>
#include <cstdint>

using namespace std;

class Benchmark
{
    public:
    typedef std::chrono::high_resolution_clock HiResClock;
    long run( int times = 10000 )
    {
        auto t0 = HiResClock::now();

        for ( auto i = 0; i < times; i ++ )
        {
            this->_run();
        }

        auto t1 = HiResClock::now();

        auto delta = std::chrono::nanoseconds(t1-t0).count();

        return delta;
    }

    private:
    void virtual _run() = 0;
};

class StringToInt : public Benchmark
{
    private:
    void _run() override
    {
        const char* nums[] = { "123456", "994636328", "2437575" };

        for( auto& n : nums )
        {
            uint64_t i = std::strtoull( n, nullptr, 10 );
        }
    }
};

class StringToIntVec : public Benchmark
{
    private:
    void _run() override
    {
        vector<const char*> nums = { "123456", "994636328", "2437575" };

        for( auto& n : nums )
        {
            uint64_t i = std::strtoull( n, nullptr, 10 );
        }
    }
};

template <typename T>
void runTest()
{
    T t;

    regex re("^[0-9]*(.*)$");
    auto name = typeid(t).name();
    auto classname = regex_replace( name, re, "$1" );

    cout << "Running..." << classname;

    auto dur = t.run(10'000'000);

    float durf = dur / 1'000'000'000.0;

    cout << endl;

    cout << "Took: " << durf << " secs" << endl;
}
