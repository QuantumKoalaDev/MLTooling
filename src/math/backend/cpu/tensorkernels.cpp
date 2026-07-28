#include <mlt/internal/math/backend/cpu/tensorkernels.hpp>

#include <cmath>

using namespace mlt::math::backend::cpu;

void elwise_add_f32_loop(float* RESTRICT a, const float* RESTRICT b, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] += b[i];
}

void elwise_add_f32_loop(float* RESTRICT a, const float scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] += scalar;
}

void elwise_add_f64_loop(double* RESTRICT a, const double* RESTRICT b, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] += b[i];
}

void elwise_add_f64_loop(double* RESTRICT a, const double scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] += scalar;
}

void elwise_sub_f32_loop(float* RESTRICT a, const float* RESTRICT b, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] += b[i];
}

void elwise_sub_f32_loop(float* RESTRICT a, const float scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] -= scalar;
}

void elweise_sub_f64_loop(double* RESTRICT a, const double* RESTRICT b, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] -= b[i];
}

void elweise_sub_f64_loop(double* RESTRICT a, const double scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] -= scalar;
}

void elwise_mul_f32_loop(float* RESTRICT a, const float* RESTRICT b, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] *= b[i];
}

void elwise_mul_f32_loop(float* RESTRICT a, const float scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] += scalar;
}

void elweise_mul_f64_loop(double* RESTRICT a, const double* RESTRICT b, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] *= b[i];
}

void elweise_mul_f64_loop(double* RESTRICT a, const double scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] *= scalar;
}

void elwise_div_f32_loop(float* RESTRICT a, const float* RESTRICT b, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] /= b[i];
}

void elwise_div_f32_loop(float* RESTRICT a, const float scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] /= scalar;
}

void elwise_div_f64_loop(double* RESTRICT a, const double* RESTRICT b, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] /= b[i];
}

void elwise_div_f64_loop(double* RESTRICT a, const double scalar, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] /= scalar;
}

void elweise_exp_f32_loop(float* RESTRICT a, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] = std::exp(a[i]);
}

void elweise_exp_f64_loop(double* RESTRICT a, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] = std::exp(a[i]);
}

float elwise_sum_f32_loop(const float* RESTRICT a, size_t n)
{
    float res = 0.f;

    for (size_t i = 0; i < n; ++i)
        res += a[i];
    
    return res;
}

double elwise_sum_f64_loop(const double* RESTRICT a, size_t n)
{
    double res = 0.0;
    
    for (size_t i = 0; i < n; ++i)
        res += a[i];
    
    return res;
}
