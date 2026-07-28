#pragma once

#include <mlt/internal/math/criticaldef.hpp>

#include <cstddef>

namespace mlt::math::backend::cpu 
{
    void elwise_add_f32_loop(
        float* RESTRICT a,
        const float* RESTRICT b,
        size_t n
    );
    
    void elwise_add_f32_loop(
        float* RESTRICT a,
        float scalar,
        size_t n
    );

    void elwise_add_f64_loop(
        double* RESTRICT a,
        const double* RESTRICT b,
        size_t n
    );
    
    void elwise_add_f64_loop(
        double* RESTRICT a,
        double scalar,
        size_t n
    );

    void elwise_sub_f32_loop(
        float* RESTRICT a,
        const float* RESTRICT b,
        size_t n
    );
    
    void elwise_sub_f32_loop(
        float* RESTRICT a,
        float scalar,
        size_t n
    );
    
    void elweise_sub_f64_loop(
        double* RESTRICT a,
        const double* RESTRICT b,
        size_t n
    );
    
    void elweise_sub_f64_loop(
        double* RESTRICT a, 
        double scalar, 
        size_t n
    );

    void elwise_mul_f32_loop(
        float* RESTRICT a,
        const float* RESTRICT b,
        size_t n
    );
    
    void elwise_mul_f32_loop(
        float* RESTRICT a,
        float scalar,
        size_t n
    );

    void elweise_mul_f64_loop(
        double* RESTRICT a,
        const double* RESTRICT b,
        size_t n
    );
    
    void elweise_mul_f64_loop(
        double* RESTRICT a,
        double scalar,
        size_t n
    );
 
    void elwise_div_f32_loop(
        float* RESTRICT a,
        const float* b,
        size_t n
    );
    
    void elwise_div_f32_loop(
        float* RESTRICT a,
        float scalar,
        size_t n
    );

    void elwise_div_f64_loop(
        double* RESTRICT a,
        const double* RESTRICT b,
        size_t n
    );
    
    void elwise_div_f64_loop(
        double* RESTRICT a,
        double scalar,
        size_t n
    );
    
    void elweise_exp_f32_loop(float* RESTRICT a, size_t n);
    void elweise_exp_f64_loop(double* RESTRICT a, size_t n);

    float elwise_sum_f32_loop(const float* RESTRICT a, size_t n);
    double elwise_sum_f64_loop(const double* RESTRICT a, size_t n);
}
