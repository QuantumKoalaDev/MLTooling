#pragma once

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <cstddef>

#include <mlt/internal/math/criticaldef.hpp>

namespace mlt::compute::backend::cpu {
    void matmul_f32(const float* a, const float* b, float* c, int64_t m, int64_t k, int64_t n);
    void add_f32(const float* a, const float* b, float* c, int64_t n);
    void mul_f32(const float* a, const float* b, float* c, int64_t n);
    void sum_f32(const float* a, float* res, int64_t n);
    void sigmoid(const float* a, float* c, int64_t n);

    void matmul(
        const std::floating_point auto* RESTRICT a,
        const std::floating_point auto* RESTRICT b,
        std::floating_point auto* RESTRICT c,
        size_t m,
        size_t k,
        size_t n
    )
    {
        for (size_t i = 0; i < m; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                auto acc = 0.0;
            
                for (size_t p = 0; p < k; ++p)
                    acc += a[i*k + p] * b[p*n + j];
            
                c[i*n +j] = acc;
            }
        }
    }

    void matmulTiled(
        const std::floating_point auto* RESTRICT a,
        const std::floating_point auto* RESTRICT b,
        std::floating_point auto* RESTRICT c,
        size_t m,
        size_t k,
        size_t n
    )
    {
        constexpr size_t TILE = 96;
    
        for (size_t iTile = 0; iTile < m; iTile += TILE)
        {
            for (size_t jTile = 0; jTile < n; jTile += TILE)
            {
                for (size_t pTile = 0; pTile < k; pTile += TILE)
                {
                    const size_t iEnd = std::min(iTile + TILE, m);
                    const size_t jEnd = std::min(jTile + TILE, n);
                    const size_t pEnd = std::min(pTile + TILE, k);

                    for (size_t i = iTile; i < iEnd; ++i)
                    {
                        for (size_t p = pTile; p < pEnd; ++p)
                        {
                            const auto ip = a[i*k + p];

                            for (size_t j = jTile; j < jEnd; ++j)
                            {
                                const auto prev = c[i*n + j];
                                c[i*n + j] = prev + ip * b[p*n + j];
                            }
                        }
                    }
                }
            }
        }
    }
}
