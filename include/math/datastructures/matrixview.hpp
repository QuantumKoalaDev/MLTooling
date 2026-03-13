#pragma once

#include <math/mathstatus.hpp>

#include <cstddef>

namespace mlt::math::datastructures
{

    struct MatrixFloatView
    {
        float* const data;
        size_t rows;
        size_t cols;
        size_t colStride;
        size_t rowStride;
    };

    struct MatrixDoubleView
    {
        double* const data;
        size_t rows;
        size_t cols;
        size_t colStride;
        size_t rowStride;
    };

    inline mathStatus checkShapeFloat(const MatrixFloatView& n, const MatrixFloatView& m)
    {
        if (n.rows != m.rows)
            return MATH_SHAPE_MISSMATCH;

        if (n.cols != m.cols)
            return MATH_SHAPE_MISSMATCH;

        return MATH_SUCCESS;
    }

    inline mathStatus checkShapeDouble(const MatrixDoubleView& n, const MatrixDoubleView& m)
    {
        if (n.rows != m.rows)
            return MATH_SHAPE_MISSMATCH;

        if (n.cols != m.cols)
            return MATH_SHAPE_MISSMATCH;

        return MATH_SUCCESS;
    }

    inline mathStatus getFlaot(const size_t row, const size_t col, const MatrixFloatView& view, float& out)
    {
        if (row >= view.rows || col >= view.cols)
            return MATH_MATRIX_OUT_OF_BOUND;

        size_t pos = col * view.colStride + row * view.rowStride;
        out = view.data[pos];

        return MATH_SUCCESS;
    }

    inline mathStatus getDouble(const size_t row, const size_t col, const MatrixDoubleView& view, double& out)
    {
        if (row >= view.rows || col >= view.cols)
            return MATH_MATRIX_OUT_OF_BOUND;

        size_t pos = col * view.colStride + row * view.rowStride;
        out = view.data[pos];

        return MATH_SUCCESS;
    }
} // namespace mlt::math::datastructures
