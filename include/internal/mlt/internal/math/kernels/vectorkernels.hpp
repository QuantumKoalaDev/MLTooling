#pragma once

#include <stddef.h>
#include <concepts>

#include <mlt/internal/math/criticaldef.hpp>
#include <mlt/internal/math/mathstatus.hpp>

namespace mlt::math::kernels
{
    template <typename T>
    concept MathTypes = 
        std::same_as<T, float> ||
        std::same_as<T, double>;

    template <MathTypes T>
    [[nodiscard]] T dot(
        const T* x, size_t n, size_t incX,
        const T* y, size_t incY
    )
    {
        const T* RESTRICT xr = x;
        const T* RESTRICT yr = y;
        
        T result = T{0};
        
        for (size_t elem = 0; elem < n; ++elem)
        {
            const size_t posX = elem * incX;
            const size_t posY = elem * incY;
     
            result += xr[posX] * yr[posY];
        }

        return result;
    }

    template <MathTypes T>
    void hadamard(
        T* x, size_t n, size_t incX,
        const T* y, size_t incY
    )
    {
        T* RESTRICT xr = x;
        const T* RESTRICT yr = y;
    
        for (size_t elem = 0; elem < n; ++elem)
        {
            const size_t posX = elem * incX;
            const size_t posY = elem * incY;
            
            xr[posX] = xr[posX] * yr[posY];
        }
    }

    // #TODO cross-product => only 3d vectors
}
