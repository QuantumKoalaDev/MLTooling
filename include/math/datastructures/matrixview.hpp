#pragma once

#include <cstddef>

namespace mlt::math::datastructures
{

    struct MatrixFloatView
    {
        const float* data;
        size_t rows;
        size_t cols;
        size_t colStride;
        size_t rowStride;
    };

    struct MatrixDoubleView
    {
        const double* data;
        size_t rows;
        size_t cols;
        size_t colStride;
        size_t rowStride;
    };
} // namespace mlt::math::datastructures
