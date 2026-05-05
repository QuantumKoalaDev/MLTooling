#pragma once

#include <cstddef>
#include <mlt/internal/math/kernels/vectorkernels.hpp>

namespace mlt::math::kernels 
{
    template <typename  T> struct VectorKernel;

    template <> struct VectorKernel<float>
    {
        [[nodiscard]] static float dot(
            float* x, size_t n, size_t incX,
            const float* y, size_t incY
        )
        {
            return mlt::math::kernels::dot<float>(x, n, incX, y, incY);
        }
        
        static void hadamard(
            float* x, size_t n, size_t incX,
            const float* y, size_t incY
        )
        {
            mlt::math::kernels::hadamard<float>(x, n, incX, y, incY);
        }
    };

    template<> struct VectorKernel<double>
    {
        [[nodiscard]] static double dot(
            double* x, size_t n, size_t incX,
            const double* y, size_t incY
        )
        {
            return mlt::math::kernels::dot<double>(x, n, incX, y, incY);
        }
        
        static void hadamard(
            double* x, size_t n, size_t incX,
            const double* y, size_t incY
        )
        {
            mlt::math::kernels::hadamard<double>(x, n, incX, y, incY);
        }
    };
}

