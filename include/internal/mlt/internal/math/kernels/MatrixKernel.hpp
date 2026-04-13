#pragma once

#include <mlt/internal/math/datastructures/matrix.hpp>
#include <mlt/internal/math/datastructures/matrixview.hpp>
#include <mlt/internal/math/kernels/matrixkernels.hpp>
#include <mlt/internal/math/mathstatus.hpp>

namespace mlt::math::kernels
{
    template <typename T> struct MatrixKernel;

    template <> struct MatrixKernel<float>
    {
        using ViewType = datastructures::MatrixFloatView;

        [[nodiscard]] static mlt::math::mathStatus
        get(const size_t row, const size_t col, const ViewType& view, float& out)
        {
            return datastructures::getFloat(row, col, view, out);
        }

        [[nodiscard]] static mlt::math::mathStatus
        set(const size_t row, const size_t col, const ViewType& view, float val)
        {
            return datastructures::setFloat(row, col, view, val);
        }

        [[nodiscard]] static mlt::math::mathStatus
        add(const ViewType& summandOne, const ViewType& summandTwo, ViewType& result)
        {
            return addMatrixFloat(summandOne, summandTwo, result);
        };

        [[nodiscard]] static mlt::math::mathStatus addInPlace(ViewType& target, const ViewType& addend)
        {
            return addMatrixFloatInPlace(target, addend);
        };

        [[nodiscard]] static mlt::math::mathStatus
        multiply(const ViewType& multiplicant, const ViewType& multiplier, ViewType& product)
        {
            return multiplyMatrixFloat(multiplicant, multiplier, product);
        };

        [[nodiscard]] static mlt::math::mathStatus
        multiplyScalar(const ViewType& mat, const float scalar, ViewType& result)
        {
            return multiplyScalarMatrixFloat(mat, scalar, result);
        };

        [[nodiscard]] static mlt::math::mathStatus multiplyScalarInPlace(ViewType& mat, const float scalar)
        {
            return multiplyScalarMatrixFloatInPlace(mat, scalar);
        };

        [[nodiscard]] static mlt::math::mathStatus clone(const ViewType& src, ViewType& dist)
        {
            return cloneMatrixFloat(src, dist);
        };
    };

    template <> struct MatrixKernel<double>
    {
        using ViewType = datastructures::MatrixDoubleView;

        [[nodiscard]] static mlt::math::mathStatus
        get(const size_t row, const size_t col, const ViewType& view, double& out)
        {
            return datastructures::getDouble(row, col, view, out);
        }

        [[nodiscard]] static mlt::math::mathStatus
        set(const size_t row, const size_t col, const ViewType& view, double val)
        {
            return datastructures::setDouble(row, col, view, val);
        }

        [[nodiscard]] static mlt::math::mathStatus
        add(const ViewType& summandOne, const ViewType& summandTwo, ViewType& result)
        {
            return addMatrixDouble(summandOne, summandTwo, result);
        };

        [[nodiscard]] static mlt::math::mathStatus addInPlace(ViewType& target, const ViewType& addend)
        {
            return addMatrixDoubleInPlace(target, addend);
        };

        [[nodiscard]] static mlt::math::mathStatus
        multiply(const ViewType& multiplicant, const ViewType& multiplier, ViewType& product)
        {
            return multiplyMatrixDouble(multiplicant, multiplier, product);
        };

        [[nodiscard]] static mlt::math::mathStatus
        multiplyScalar(const ViewType& mat, const double scalar, ViewType& result)
        {
            return multiplyScalarMatrixDouble(mat, scalar, result);
        };

        [[nodiscard]] static mlt::math::mathStatus multiplyScalarInPlace(ViewType& mat, const double scalar)
        {
            return multiplyScalarMatrixDoubleInPlace(mat, scalar);
        };

        [[nodiscard]] static mlt::math::mathStatus clone(const ViewType& src, ViewType& dist)
        {
            return cloneMatrixDouble(src, dist);
        };
    };
} // namespace mlt::math::kernels
