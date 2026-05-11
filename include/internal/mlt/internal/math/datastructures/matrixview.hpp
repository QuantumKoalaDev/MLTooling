#pragma once

#include <mlt/internal/math/mathstatus.hpp>

#include <cstddef>
#include <system_error>

namespace mlt::math
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

    inline mathStatus getFloat(const size_t row, const size_t col, const MatrixFloatView& view, float& out)
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

    inline mathStatus setFloat(const size_t row, const size_t col, const MatrixFloatView& view, float val)
    {
        if (row >= view.rows || col >= view.cols)
            return MATH_MATRIX_OUT_OF_BOUND;

        const size_t pos = col * view.colStride + row * view.rowStride;
        view.data[pos] = val;

        return MATH_SUCCESS;
    }

    inline mathStatus setDouble(const size_t row, const size_t col, const MatrixDoubleView& view, double val)
    {
        if (row >= view.rows || col >= view.cols)
            return MATH_MATRIX_OUT_OF_BOUND;

        const size_t pos = col * view.colStride + row * view.rowStride;
        view.data[pos] = val;

        return MATH_SUCCESS;
    }
} // namespace mlt::math
