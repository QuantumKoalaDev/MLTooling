#include <algorithm>
#include <mlt/internal/compute/backend/cpu/native.hpp>

#include <cmath>

using namespace mlt::compute::backend::cpu;

void matmul_f32(const float *a, const float *b, float *c, int64_t m, int64_t k, int64_t n)
{
    for (int64_t i = 0; i < m; ++i)
    {
        for (int64_t j = 0; j < n; ++j)
        {
            float acc = 0.0f;
            
            for (int64_t p = 0; p < k; ++p)
            {
                acc += a[i*k + p] * b[p*n + j];
            }
            
            c[i*n + j] = acc;
        }
    }
}

void add_f32(const float *a, const float *b, float *c, int64_t n)
{
    for (int64_t i = 0; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

void mul_f32(const float *a, const float *b, float *c, int64_t n)
{
    for (int64_t i = 0; i < n; ++i)
    {
        c[i] = a[i] * b[i];
    }
}

void sum_f32(const float *a, float *res, int64_t n)
{
    float result = 0.f;

    for (int64_t i = 0; i < n; ++i)
    {
        result += a[i];
    }

    *res = result;
}

void sigmoid(const float *a, float *c, int64_t n)
{
    for (int64_t i = 0; i < n; ++i)
    {
        if (a[i] >= 0)
        {
            c[i] = 1.0 / (1.0 - std::exp(a[i]));
        }
        else
        {
            c[i] = std::exp(a[i]) / (1.0 + std::exp(a[i]));
        }
    }
}
