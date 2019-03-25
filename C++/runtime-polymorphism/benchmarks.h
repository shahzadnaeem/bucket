
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
    long run( int times = 10'000 )
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

template <typename T, int count = 10'000'000>
void runTest()
{
    T t;
    auto const nsecToSecs = 1'000'000'000.0;

    regex re("^[0-9]*(.*)$");
    auto name = typeid(t).name();
    auto classname = regex_replace( name, re, "$1" );

    cout << "Running: " << classname << ", " << count << " times..." << flush;

    auto dur = t.run(count);

    float durf = dur / nsecToSecs;

    cout << endl;

    cout << "Took: " << durf << " secs" << endl;
}
