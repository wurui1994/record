#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>

#define USE_SIMDE

#ifndef USE_SIMDE
#include <intrin.h>
#else
#define SIMDE_TESTS_CURRENT_ISAX sse
#include <simde/x86/sse2.h>
#endif

using namespace std;

class Profiler
{
public:
    Profiler(const string &tag)
        : m_Tag(tag), m_StartTime(chrono::steady_clock::now())
    {
    }
    ~Profiler()
    {
        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - m_StartTime).count();
        cout << m_Tag << " 耗时: " << duration << " ms" << endl;
    }

private:
    string m_Tag;
    chrono::steady_clock::time_point m_StartTime;
};

int main()
{
    int count = 100000000;
    int time = 10;
    float *buf = new float[count];
    for (int i = 0; i < count; ++i)
    {
        buf[i] = (float)rand() / RAND_MAX;
    }
    for (int t = 0; t < time; ++t)
    {
        auto profiler = Profiler("No SIMD Test");
        #pragma loop(no_vector)   // GCC禁用自动向量化
        for (int i = 0; i < count; ++i)
        {
            float a = buf[i];
            a = a * a;
            buf[i] = a;
        }
    }
    for (int t = 0; t < time; ++t)
    {
        auto profiler = Profiler("SSE Test");
        for (int i = 0; i < count; i += 4)
        {
#ifndef USE_SIMDE
            __m128 a = _mm_loadu_ps(buf + i);
            a = _mm_mul_ps(a, a);
            _mm_storeu_ps(buf + i, a);
#else
            simde__m128 a = simde_mm_loadu_ps(buf+i);
            a = simde_mm_mul_ps(a, a);
            simde_mm_storeu_ps(buf + i, a);
#endif
        }
    }
    delete[] buf;
    return 0;
}