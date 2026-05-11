#pragma once

#include <mlt/internal/math/datastructures/matrixview.hpp>
#include <mlt/internal/math/mathstatus.hpp>

namespace mlt::math::kernels
{
    [[nodiscard]] mathStatus addMatrixFloat(
        const MatrixFloatView& summandOne, const MatrixFloatView& summandTwo,
        MatrixFloatView& result
    );

    [[nodiscard]] mathStatus addMatrixDouble(
        const MatrixDoubleView& summandOne, const MatrixDoubleView& summandTwo,
        MatrixDoubleView& result
    );

    [[nodiscard]] mathStatus
    addMatrixFloatInPlace(MatrixFloatView& target, const MatrixFloatView& addend);

    [[nodiscard]] mathStatus
    addMatrixDoubleInPlace(MatrixDoubleView& target, const MatrixDoubleView& addend);

    [[nodiscard]] mathStatus subtractMatrixFloat(
        const MatrixFloatView& minuend, const MatrixFloatView& subtrahend,
        MatrixFloatView& difference
    );

    [[nodiscard]] mathStatus subtractMatrixDouble(
        const MatrixDoubleView& minuend, const MatrixDoubleView& subtrahend,
        MatrixDoubleView& difference
    );

    [[nodiscard]] mathStatus subtractInPlaceMatrixFloat(
        MatrixFloatView& difference, const MatrixFloatView& subtrahend
    );

    [[nodiscard]] mathStatus subtractInPlaceMatrixDouble(
        MatrixDoubleView& difference, const MatrixDoubleView& subtrahend
    );

    [[nodiscard]] mathStatus multiplyMatrixFloat(
        const MatrixFloatView& multiplicant, const MatrixFloatView& multiplier,
        MatrixFloatView& product
    );

    [[nodiscard]] mathStatus multiplyMatrixDouble(
        const MatrixDoubleView& multiplicant, const MatrixDoubleView& multiplier,
        MatrixDoubleView& product
    );

    [[nodiscard]] mathStatus multiplyScalarMatrixFloat(
        const MatrixFloatView& mat, float scalar, MatrixFloatView& result
    );

    [[nodiscard]] mathStatus multiplyScalarMatrixDouble(
        const MatrixDoubleView& mat, double scalar, MatrixDoubleView& result
    );

    [[nodiscard]] mathStatus multiplyScalarMatrixFloatInPlace(MatrixFloatView& mat, float scalar);

    [[nodiscard]] mathStatus multiplyScalarMatrixDoubleInPlace(MatrixDoubleView& mat, double scalar);

    [[nodiscard]] mathStatus
    cloneMatrixFloat(const MatrixFloatView& src, MatrixFloatView& dist);

    [[nodiscard]] mathStatus
    cloneMatrixDouble(const MatrixDoubleView& src, MatrixDoubleView& dist);

    // kernels
    // mlt::math::mathStatus getRowFloat(MatrixFloatView& matView, size_t row, float* out);
    // mlt::math::mathStatus getColFloat(MatrixFloatView& matView, size_t col, float* out);
    // mlt::math::mathStatus transpose(const MatrixFloatView& src, MatrixFloatView& dist);
    // mlt::math::mathStatus fill(MatrixFloatView& mat, float value);
    // mlt::math::mathStatus setZero(MatrixFloatView& mat);
    // mlt::math::mathStatus setIdentity(MatrixFloatView& mat);

} // namespace mlt::math::kernels
